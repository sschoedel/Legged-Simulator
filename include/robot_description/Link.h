#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include <math.h>

typedef struct
{
    float maxTorque;
    float maxAccel;
    float maxCurrent;
    float torque;
    float accel;
    float vel;
    float pos;
    float current;
} motorStats;

// Each link is assumed to have a motor attached directly to an axis of rotation
class Link { 
    public:
        Link() {};
        void setup(bool _isRoot, float _mass, std::string _name, const ci::geom::Source &shape, ci::gl::GlslProgRef mGlslShadow, ci::vec3 _size, std::vector<std::pair<ci::vec3, ci::vec3>> _mountingPoints, int _thisMountIndex, int _parentMountIndex);
        void setPoseOffset();
        void addChild(Link link);
        void addParent(Link link);
        void clearChildren();
        void clearParents();
        void assignBatches(const ci::geom::Source &shape, ci::gl::GlslProgRef mGlslShadow);

        // link variable visualization
        void drawMountingPtLines();
        void drawMountingPtAxes();
        void drawJointGeomCenterAxes();
        void drawMotorRotationBounds();
        void drawMotorCommandedTorques();

        // Ease of use drawing functions;
        void drawVector( const ci::vec3& start, const ci::vec3& end, float headLength, float headRadius, float shaftRadius);
        void drawCoordinateFrame( float axisLength, float headLength, float headRadius, float shaftRadius );

        glm::vec3           mountingPosition, baseOrientation;
        glm::vec3           firstRotationPosition, firstRotationAxis;
        glm::vec3           secondRotationPosition, secondRotationAxis;
        glm::vec3           linkMassCenter;
        glm::vec3           centerPos;
        glm::vec3           centerRot;

        glm::mat4           pose;
        glm::mat4           poseOffset;
        ci::vec3            poseTransOffset;
        ci::vec3            poseRotOffset;
        float               jointAngle;

        motorStats          motor;

        bool                visible;
        bool                isRoot;

        std::vector<Link>   parents;
        std::vector<Link>   children;

        ci::vec3            size;
        float               mass;
	    std::vector<std::pair<ci::vec3, ci::vec3>>  mountingPoints;
        int                 thisMountIndex;
        int                 parentMountIndex;
        int                 parentIndex;

        std::string         name;
        ci::Color           pColor;
        ci::gl::BatchRef    mainBatch;
        ci::gl::BatchRef    shadowedBatch;

        // visualization semantics
        ci::Color           mountingPtLinesColor    = ci::Color(0.0,0.5,1.0); // greenish blue
        // ci::Color           mountingPtAxesColor_x   = ci::Color(1.0,0.0,0.0); // red
        // ci::Color           mountingPtAxesColor_y   = ci::Color(0.0,1.0,0.0); // green
        // ci::Color           mountingPtAxesColor_z   = ci::Color(0.0,0.0,1.0); // blue
};
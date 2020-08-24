#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include <math.h>

struct _motorStats
{
    float maxTorque;
    float maxAccel;
    float maxCurrent;
    float appliedTorque;
    float accel;
    float vel;
    float pos;
    float current;
};
typedef _motorStats MotorStats;

class Link;
typedef std::shared_ptr<Link> LinkRef;

// Each link is assumed to have a motor attached directly to an axis of rotation
class Link { 
    public:
        static LinkRef create();
        Link() {};
        void setup(bool _isRoot, float _mass, std::string _name, const ci::geom::Source &shape, ci::gl::GlslProgRef mGlslShadow, ci::vec3 _size, std::vector<std::pair<ci::vec3, ci::vec3>> _mountingPoints, 
                    int _thisMountIndex, int _parentMountIndex, ci::Color _pColor, float _zeroJointAngle, float _initialJointAngle, int _rotationDirection, int _rotationAxis);
        void setPoses();
        void updateJointPose();
        void addChild(LinkRef &link);
        void addParent(LinkRef &link);
        void clearChildren();
        void clearParents();
        void assignBatches(const ci::geom::Source &shape, ci::gl::GlslProgRef mGlslShadow);
        void updateTotalJointAngle();

        // link variable visualization
        void drawMountingPtLines();
        void drawMountingPtAxes();
        void drawJointGeomCenterAxes();
        void drawMotorRotationBounds();
        void drawMotorRotations();
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

        glm::mat4           linkPose;
        ci::vec3            linkPoseTrans;
        
        glm::mat4           jointPose;
        ci::vec3            jointPoseTrans;
        ci::vec3            jointPoseRot;
        ci::vec3            alignmentAxis;
        ci::vec3            parentRotAxis;       
        // ci::vec3        thisRotationAxis;
        int                 rotationDirection;
        int                 rotationAxis;

        float               zeroJointAngle;      // angle required for 'T-pose'
        float               initialJointAngle;
        float               jointAngle;
        float               totalJointAngle;
        float               alignmentAngle;      // used for joint alignment before applying motor angle rotation
        float               minJointAngle;
        float               maxJointAngle;

        float               torqueOnJoint;

        bool                visible;
        bool                isRoot;

        std::vector<LinkRef>   parents;
        std::vector<LinkRef>   children;

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

        // Q: What is this bug? Instantiating thisRotAxis (or any variable name) somewhere between jointPose and zeroJointAngle causes the model to not draw
        // This bug doesn't happen when its instantiated at the bottom of the header. wtf
        ci::vec3            thisRotAxis;         // the axis about which this link will rotate - same axis used to align to the previous link's mounting axis
        MotorStats          motor;
};
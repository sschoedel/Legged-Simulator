#pragma once

#include "cinder/gl/gl.h"

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
        void setup(bool _isRoot, float _mass, std::string _name, ci::gl::BatchRef _mainBatch, ci::gl::BatchRef _shadowedBatch, ci::vec3 _size, std::vector<std::pair<ci::vec3, ci::vec3>> _mountingPoints, int _thisMountIndex, int _parentMountIndex);
        void addChild(Link link);

        glm::vec3           mountingPosition, baseOrientation;
        glm::vec3           firstRotationPosition, firstRotationAxis;
        glm::vec3           secondRotationPosition, secondRotationAxis;
        glm::vec3           linkMassCenter;
        glm::vec3           centerPos;
        glm::vec3           centerRot;

        glm::mat4           pose;

        motorStats          motor;

        float               mass;

        bool                visible;
        bool                isRoot;

        std::vector<Link>   parents;
        std::vector<Link>   children;

        ci::vec3                size;
	    std::vector<std::pair<ci::vec3, ci::vec3>>  mountingPoints;
        int                     thisMountIndex;
        int                     parentMountIndex;

        std::string         name;
        ci::Color           pColor;
        ci::gl::BatchRef    mainBatch;
        ci::gl::BatchRef    shadowedBatch;
};
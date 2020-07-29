#pragma once

#include "cinder/gl/gl.h"
#include "robot_description/Link.h"
#include <vector>
#include "Mesh.h"

#include "robot_description/configs/root_config.h"
#include "robot_description/configs/upper_leg_config.h"
#include "robot_description/configs/lower_leg_config.h"
#include "robot_description/configs/shoulder_config.h"

class Robot
{
    public:
        Robot() {};
        void setup(ci::gl::GlslProgRef mGlslShadow);
        void calcPoses(Link &parent);
        void visualization();
        void clearFamily(Link &root);
        void setChildren();
        void visualizePartVars(Link &parent, std::vector<glm::mat4> prevPoses);
        
        glm::mat4 calcPartPose(float tx, float ty, float tz, float rotx, float roty, float rotz, float scale);

        // specific to each robot
        RootConfig rootConfig;
        ShoulderConfig shoulderConfig;
        UpperLegConfig upperLegConfig;
        LowerLegConfig lowerLegConfig;

        Link body;
        Link FLS, FLU, FLL;
        Link FRS, FRU, FRL;
        Link BLS, BLU, BLL;
        Link BRS, BRU, BRL;

        bool showMtPtLines;
        bool showMtPtAxes;
        bool showJointAxes;
        bool showFullRotation;
        bool showMotorTorques;
};


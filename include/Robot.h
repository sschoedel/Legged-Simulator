#pragma once

#include "cinder/gl/gl.h"
#include "robot_description/Link.h"
#include <vector>
#include "Mesh.h"

#include "robot_description/configs/root_config.h"
#include "robot_description/configs/shoulder_config_front_left.h"
#include "robot_description/configs/shoulder_config_front_right.h"
#include "robot_description/configs/shoulder_config_back_left.h"
#include "robot_description/configs/shoulder_config_back_right.h"

#include "robot_description/configs/upper_leg_config_front_left.h"
#include "robot_description/configs/upper_leg_config_front_right.h"
#include "robot_description/configs/upper_leg_config_back_left.h"
#include "robot_description/configs/upper_leg_config_back_right.h"

#include "robot_description/configs/lower_leg_config_front_left.h"
#include "robot_description/configs/lower_leg_config_front_right.h"
#include "robot_description/configs/lower_leg_config_back_left.h"
#include "robot_description/configs/lower_leg_config_back_right.h"

class Robot
{
    public: 
        Robot() {};
        void setup(ci::gl::GlslProgRef mGlslShadow);
        void calcPoses(LinkRef &parent);
        void visualization();
        void clearFamily(LinkRef &root);
        void setChildren();
        void visualizePartVars(LinkRef &parent, std::vector<glm::mat4> prevPoses);

        void calculateTorques(LinkRef &parents);
        void applyTorques(LinkRef &parent);
        
        glm::mat4 calcPartPose(float tx, float ty, float tz, float rotx, float roty, float rotz, float scale);

        // specific to each robot
        RootConfig rootConfig;
        FrontLeftShoulderConfig frontLeftShoulderConfig;
        BackLeftShoulderConfig backLeftShoulderConfig;
        FrontRightShoulderConfig frontRightShoulderConfig;
        BackRightShoulderConfig backRightShoulderConfig;

        FrontLeftUpperLegConfig frontLeftUpperLegConfig;
        FrontRightUpperLegConfig frontRightUpperLegConfig;
        BackLeftUpperLegConfig backLeftUpperLegConfig;
        BackRightUpperLegConfig backRightUpperLegConfig;

        FrontLeftLowerLegConfig frontLeftLowerLegConfig;
        FrontRightLowerLegConfig frontRightLowerLegConfig;
        FrontLeftLowerLegConfig backLeftLowerLegConfig;
        FrontRightLowerLegConfig backRightLowerLegConfig;

        LinkRef body = Link::create();
        LinkRef FLS  = Link::create();
        LinkRef FLU  = Link::create();
        LinkRef FLL  = Link::create();
        LinkRef FRS  = Link::create();
        LinkRef FRU  = Link::create();
        LinkRef FRL  = Link::create();
        LinkRef BLS  = Link::create();
        LinkRef BLU  = Link::create();
        LinkRef BLL  = Link::create();
        LinkRef BRS  = Link::create();
        LinkRef BRU  = Link::create();
        LinkRef BRL  = Link::create();

        bool showMtPtLines;
        bool showMtPtAxes;
        bool showLinkAxes;
        bool showFullRotation;
        bool showCurrentRotations;
        bool showMotorTorques;
        bool showAll;
};


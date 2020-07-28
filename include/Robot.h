#pragma once

#include "cinder/gl/gl.h"
#include "robot_description/Link.h"
#include <vector>

#include "robot_description/configs/root_config.h"
#include "robot_description/configs/upper_leg_config.h"
#include "robot_description/configs/lower_leg_config.h"
#include "robot_description/configs/shoulder_config.h"

class Robot
{
    public:
        Robot() {};
        void setup(ci::gl::GlslProgRef mGlslShadow);

        // specific to each robot
        RootConfig rootConfig;
        ShoulderConfig shoulderConfig;
        UpperLegConfig upperLegConfig;
        LowerLegConfig lowerLegConfig;

        Link root;
        Link FLS, FLU, FLL;
        Link FRS, FRU, FRL;
        Link BLS, BLU, BLL;
        Link BRS, BRU, BRL;
};
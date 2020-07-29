#pragma once

#include "cinder/gl/gl.h"
#include <vector>

class ShoulderConfig
{
    public:
        ci::vec3            size          = ci::vec3(18,7,7);
        ci::geom::Capsule   shoulderShape = ci::geom::Capsule().radius(3).length(18).direction(ci::vec3(1, 0, 0));
        ci::Color           color         = ci::Color(0.2f,0.2f,0.2f);
        float               initialJointAngle = 0;

        // Object coordinates
        std::vector<std::pair<ci::vec3, ci::vec3>> mountingPoints;
        ci::vec3            mtPt1         = ci::vec3(9,0,0);
        ci::vec3            mtPt2         = ci::vec3(-9,0,0);
        ci::vec3            mtDir1        = ci::vec3(0,0,6);
        ci::vec3            mtDir2        = ci::vec3(0,0,6);
        int             thisMountIndex    = 0;
        float           mass              = 1;
};
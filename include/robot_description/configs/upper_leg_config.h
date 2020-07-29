#pragma once

#include "cinder/gl/gl.h"
#include <vector>

class UpperLegConfig
{
    public:
        ci::vec3            size          = ci::vec3(60,8,6);
        ci::geom::Capsule   upperLegShape = ci::geom::Capsule().radius(4).length(60).direction(ci::vec3(1, 0, 0));
        ci::Color           color         = ci::Color(0.3f,0.3f,0.3f);
        float               initialJointAngle = 0;

        // Object coordinates
        std::vector<std::pair<ci::vec3, ci::vec3>> mountingPoints;
        ci::vec3            mtPt1         = ci::vec3(0,0,0);
        ci::vec3            mtPt2         = ci::vec3(0,0,0);
        ci::vec3            mtDir1        = ci::vec3(0,0,0);
        ci::vec3            mtDir2        = ci::vec3(0,0,0);
        int             thisMountIndex    = 0;
	    int             parentMountIndex  = 1;
        float           mass              = 1;
};
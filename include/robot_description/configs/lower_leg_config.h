#pragma once

#include "cinder/gl/gl.h"
#include <vector>

class LowerLegConfig
{
    public:
        ci::geom::Capsule   lowerLegShape = ci::geom::Capsule().radius(3).length(60).direction(ci::vec3(1, 0, 0));
        ci::vec3            size          = ci::vec3(60,6,4);
        std::vector<std::pair<ci::vec3, ci::vec3>> mountingPoints;
        ci::vec3            mtPt1         = ci::vec3(0,0,0);
        ci::vec3            mtPt2         = ci::vec3(0,0,0);
        ci::vec3            mtDir1        = ci::vec3(0,0,0);
        ci::vec3            mtDir2        = ci::vec3(0,0,0);
        int             thisMountIndex    = 0;
	    int             parentMountIndex  = 0;
        float           mass              = 1;
};
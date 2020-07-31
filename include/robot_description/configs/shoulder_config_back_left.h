#pragma once

#include "cinder/gl/gl.h"
#include <vector>

class BackLeftShoulderConfig
{
    public:
        int                 length            = 8;
        int                 width             = 6;
        int                 height            = width;
        ci::vec3            size              = ci::vec3(length, width, height);
        ci::geom::Capsule   shoulderShape     = ci::geom::Capsule().radius(width/2).length(length).direction(ci::vec3(1, 0, 0));
        ci::Color           color             = ci::Color(0.2f,0.2f,0.2f);

        int                 rotationDirection = -1;
        int                 rotationAxis      = 0;

        float               zeroJointAngle    = 1.571;
        float               initialJointAngle = 0;

        // Object coordinates
        std::vector<std::pair<ci::vec3, ci::vec3>> mountingPoints;
        ci::vec3            mtPt1         = ci::vec3(-length/2,0,0);
        ci::vec3            mtPt2         = ci::vec3(length/2,0,0);
        ci::vec3            mtDir1        = ci::vec3(0,0,6);
        ci::vec3            mtDir2        = ci::vec3(6,0,0);
        int             thisMountIndex    = 0;
	    int             parentMountIndex  = 0;
        float           mass              = 1;
};
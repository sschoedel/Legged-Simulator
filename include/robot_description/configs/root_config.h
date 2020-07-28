#pragma once

#include "cinder/gl/gl.h"
#include <vector>

class RootConfig
{
    public:
        ci::Color           rootColor       = ci::Color(0.2f, 0.7f, 0.5f);
        ci::geom::Capsule   rootShape	    = ci::geom::Capsule().radius(35).length(100).direction(ci::vec3(1, 0, 0));
        ci::vec3            initialrootPos  = ci::vec3(0,0,50);
        ci::vec3            initialrootRot  = ci::vec3(0,0,50);
        ci::vec3            size        = ci::vec3(100,20,35);
        std::vector<std::pair<ci::vec3, ci::vec3>> 	mountingPoints;
        ci::vec3 mtPt1  = ci::vec3(0,0,0);
        ci::vec3 mtPt2  = ci::vec3(0,0,0);
        ci::vec3 mtPt3  = ci::vec3(0,0,0);
        ci::vec3 mtPt4  = ci::vec3(0,0,0);
        ci::vec3 mtDir1 = ci::vec3(0,0,0);
        ci::vec3 mtDir2 = ci::vec3(0,0,0);
        ci::vec3 mtDir3 = ci::vec3(0,0,0);
        ci::vec3 mtDir4 = ci::vec3(0,0,0);
        float rootMass = 2; // kg
};
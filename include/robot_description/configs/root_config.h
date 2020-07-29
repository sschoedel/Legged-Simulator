#pragma once

#include "cinder/gl/gl.h"
#include <vector>

class RootConfig
{
    public:
        ci::vec3            size            = ci::vec3(40,8,20);    
        ci::geom::Cube      rootShape	    = ci::geom::Cube().size(size);
        ci::Color           rootColor       = ci::Color(0.2f, 0.7f, 0.5f);    
        
        // In object coordinates
        std::vector<std::pair<ci::vec3, ci::vec3>> 	mountingPoints;
        ci::vec3 mtPt1  = ci::vec3(20,0,-7.5);
        ci::vec3 mtPt2  = ci::vec3(20,0,7.5);
        ci::vec3 mtPt3  = ci::vec3(-20,0,-7.5);
        ci::vec3 mtPt4  = ci::vec3(-20,0,7.5);
        ci::vec3 mtDir1 = ci::vec3(6,0,0);
        ci::vec3 mtDir2 = ci::vec3(6,0,0);
        ci::vec3 mtDir3 = ci::vec3(-6,0,0);
        ci::vec3 mtDir4 = ci::vec3(-6,0,0);
        float rootMass = 2; // kg

        // In world coordinates
        ci::vec3            initialrootPos  = ci::vec3(0,30,0);
        ci::vec3            initialrootRot  = ci::vec3(0,0,0);
};
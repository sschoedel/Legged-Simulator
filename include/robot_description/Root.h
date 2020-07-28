#pragma once

#include "cinder/gl/gl.h"
#include "Link.h"

class Root {
    public:
        Root() {};
        void setup(float _mass, std::string _name, ci::gl::BatchRef _mainBatch, ci::gl::BatchRef _shadowedBatch, ci::vec3 _pos, ci::vec3 _rot, ci::vec3 _size, std::vector<std::pair<ci::vec3, ci::vec3>> _mountingPoints);
        void addChild(Link link);

        glm::vec3           rootPhysicalCenter, rootOrientation;
        glm::vec3           rootMassCenter;

        float               mass; // kg

        bool                visible;

        std::vector<Link>   children;

        ci::vec3                                    pos;
        ci::vec3                                    rot;
        ci::vec3                                    size;
	    std::vector<std::pair<ci::vec3, ci::vec3>>  mountingPoints;

        std::string         name;
        ci::Color           pColor;
        ci::gl::BatchRef    mainBatch;
        ci::gl::BatchRef    shadowedBatch;
};
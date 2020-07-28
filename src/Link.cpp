#include "robot_description/Link.h"

void Link::setup(bool _isRoot, float _mass, std::string _name, ci::gl::BatchRef _mainBatch, ci::gl::BatchRef _shadowedBatch, ci::vec3 _size, std::vector<std::pair<ci::vec3, ci::vec3>> _mountingPoints, int _thisMountIndex, int _parentMountIndex)
{
    isRoot = _isRoot;
	visible = true;
	mass = _mass;
	name = _name;
	mainBatch = _mainBatch;
	shadowedBatch = _shadowedBatch;
	size = _size;
	mountingPoints = _mountingPoints;
	thisMountIndex = _thisMountIndex;
	parentMountIndex = _parentMountIndex;
}

void Link::addChild(Link link)
{
	children.push_back(link);
}
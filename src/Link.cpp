#include "robot_description/Link.h"

LinkRef Link::create()
{
	LinkRef ref = std::make_shared<Link>();
	return ref;
}

void Link::setup(bool _isRoot, float _mass, std::string _name, const ci::geom::Source &shape, ci::gl::GlslProgRef mGlslShadow, ci::vec3 _size, std::vector<std::pair<ci::vec3, ci::vec3>> _mountingPoints, 
					int _thisMountIndex, int _parentMountIndex, ci::Color _pColor, float _initialJointAngle, int _rotationDirection, int _rotationAxis)
{
	shadowedBatch    	= ci::gl::Batch::create(shape, mGlslShadow);
	mainBatch        	= ci::gl::Batch::create(shape, ci::gl::getStockShader(ci::gl::ShaderDef()));
	visible          	= true;
    isRoot           	= _isRoot;
	name             	= _name;
	mass             	= _mass;
	size             	= _size;
	mountingPoints   	= _mountingPoints;
	thisMountIndex   	= _thisMountIndex;
	parentMountIndex 	= _parentMountIndex;
	parentIndex		 	= 0; // Each link only supports one parent for now
	pColor			 	= _pColor;
	initialJointAngle 	= _initialJointAngle;
	rotationDirection	= _rotationDirection;
	rotationAxis		= _rotationAxis;
}

void Link::setPoses()
{
	if (!isRoot)
	{
		if (static_cast<int>(parents.size()) > parentIndex)
		{
			fprintf(stderr, "\nSetting joint pose for joint "); std::cout << name << std::endl;

			updateTotalJointAngle();

			jointPoseTrans     = parents[parentIndex]->mountingPoints[parentMountIndex].first;
			ci::vec3 thisRotAxis   = mountingPoints[thisMountIndex].second;
			parentRotAxis = normalize( parents[parentIndex]->mountingPoints[parentMountIndex].second );

			// ci::vec3 x_axis(1,0,0);
			// ci::vec3 y_axis(0,1,0);
			// ci::vec3 z_axis(0,0,1);

			// ci::vec2 thisRot_zy(thisRot.z, thisRot.y);
			// ci::vec2 thisRot_xz(thisRot.x, thisRot.z);
			// ci::vec2 thisRot_yx(thisRot.y, thisRot.x);
			// ci::vec2 parentRot_zy(parentRot.z, parentRot.y);
			// ci::vec2 parentRot_xz(parentRot.x, parentRot.z);
			// ci::vec2 parentRot_yx(parentRot.y, parentRot.x);

			// jointPoseRot.x = acos( ci::dot( thisRot_zy, parentRot_zy ) );
			// jointPoseRot.y = acos( ci::dot( thisRot_xz, parentRot_xz ) );
			// jointPoseRot.z = acos( ci::dot( thisRot_yx, parentRot_yx ) );

			// if (rotationAxis == 0)
			// {
			// 	jointPose  = glm::translate ( jointPoseTrans )
			// 			   * glm::toMat4 ( glm::angleAxis( rotationDirection * (zeroJointAngle + initialJointAngle), ci::vec3 ( 1, 0, 0 ) ) )
			// 			   * glm::toMat4 ( glm::angleAxis( jointPoseRot.y, ci::vec3 ( 0, 1, 0 ) ) )
			// 			   * glm::toMat4 ( glm::angleAxis( jointPoseRot.z, ci::vec3 ( 0, 0, 1 ) ) );
			// }
			// else if (rotationAxis == 1)
			// {
			// 	jointPose  = glm::translate ( jointPoseTrans )
			// 			   * glm::toMat4 ( glm::angleAxis( jointPoseRot.x, ci::vec3 ( 1, 0, 0 ) ) )
			// 			   * glm::toMat4 ( glm::angleAxis( rotationDirection * (zeroJointAngle + initialJointAngle), ci::vec3 ( 0, 1, 0 ) ) )
			// 			   * glm::toMat4 ( glm::angleAxis( jointPoseRot.z, ci::vec3 ( 0, 0, 1 ) ) );
			// }
			// else if (rotationAxis == 2)
			// {
			// 	jointPose  = glm::translate ( jointPoseTrans )
			// 			   * glm::toMat4 ( glm::angleAxis( jointPoseRot.x, ci::vec3 ( 1, 0, 0 ) ) )
			// 			   * glm::toMat4 ( glm::angleAxis( jointPoseRot.y, ci::vec3 ( 0, 1, 0 ) ) )
			// 			   * glm::toMat4 ( glm::angleAxis( rotationDirection * (zeroJointAngle + initialJointAngle), ci::vec3 ( 0, 0, 1 ) ) );
			// }

			// always align the z-axis of next joint to mountingPoint of previous link using axis alignment


			alignmentAngle = acos( dot(thisRotAxis, parentRotAxis) );
			alignmentAxis = normalize( cross(thisRotAxis, parentRotAxis) );
			fprintf(stderr, "\nalignmentaxis: %f, %f, %f", alignmentAxis.x, alignmentAxis.y, alignmentAxis.z);
			fprintf(stderr, "\nalignmentangle: %f",alignmentAngle);

			jointPose = glm::translate( jointPoseTrans )
					  * glm::toMat4( glm::angleAxis( alignmentAngle, alignmentAxis ) )
			   		  * glm::toMat4( glm::angleAxis( totalJointAngle, parentRotAxis ) );
		}
		else
		{
			fprintf(stderr, "\nWARN: Fewer parents than parent index, can't set joint or link poses");
		}

		fprintf(stderr, "\nSetting link pose for link "); std::cout << name << std::endl;
		// TODO: change offset for left and right legs (should make config files for each side instead of doing it in link.cpp)

		// set once (unless linear actuator, then arm needs to extend and this would be updated accordingly)
		linkPoseTrans.x = size.x/2;
		linkPoseTrans.y = 0;
		linkPoseTrans.z = 0;
		linkPose        = glm::translate ( linkPoseTrans );
	}

}

void Link::updateJointPose()
{
	updateTotalJointAngle();
	// if (rotationAxis == 0)
	// {
	// 	jointPose  = glm::translate ( jointPoseTrans )
	// 			* glm::toMat4 ( glm::angleAxis( rotationDirection * totalJointAngle, ci::vec3 ( 1, 0, 0 ) ) )
	// 			* glm::toMat4 ( glm::angleAxis( jointPoseRot.y, ci::vec3 ( 0, 1, 0 ) ) )
	// 			* glm::toMat4 ( glm::angleAxis( jointPoseRot.z, ci::vec3 ( 0, 0, 1 ) ) );
	// }
	// else if (rotationAxis == 1)
	// {
	// 	jointPose  = glm::translate ( jointPoseTrans )
	// 			* glm::toMat4 ( glm::angleAxis( jointPoseRot.x, ci::vec3 ( 1, 0, 0 ) ) )
	// 			* glm::toMat4 ( glm::angleAxis( rotationDirection * totalJointAngle, ci::vec3 ( 0, 1, 0 ) ) )
	// 			* glm::toMat4 ( glm::angleAxis( jointPoseRot.z, ci::vec3 ( 0, 0, 1 ) ) );
	// }
	// else if (rotationAxis == 2)
	// {
	// 	jointPose  = glm::translate ( jointPoseTrans )
	// 			* glm::toMat4 ( glm::angleAxis( jointPoseRot.x, ci::vec3 ( 1, 0, 0 ) ) )
	// 			* glm::toMat4 ( glm::angleAxis( jointPoseRot.y, ci::vec3 ( 0, 1, 0 ) ) )
	// 			* glm::toMat4 ( glm::angleAxis( rotationDirection * totalJointAngle, ci::vec3 ( 0, 0, 1 ) ) );
	// }
	jointPose  = glm::translate ( jointPoseTrans )
			   * glm::toMat4( glm::angleAxis( alignmentAngle, alignmentAxis ) )
			   * glm::toMat4( glm::angleAxis( totalJointAngle, parentRotAxis ) );
}

void Link::updateTotalJointAngle()
{
	totalJointAngle = zeroJointAngle + initialJointAngle + jointAngle;
}

void Link::addChild(LinkRef &link)
{
	children.push_back(link);
}

void Link::addParent(LinkRef &link)
{
	parents.push_back(link);
}

void Link::clearChildren()
{
	children.clear();
}

void Link::clearParents()
{
	parents.clear();
}

// visualization
void Link::drawMountingPtLines()
{
    ci::gl::ScopedGlslProg shader( ci::gl::getStockShader( ci::gl::ShaderDef().color().lambert() ) );
    ci::gl::ScopedColor color( mountingPtLinesColor );
    for ( std::pair<ci::vec3, ci::vec3> line : mountingPoints )
    {
        drawVector(line.first + line.second, line.first, 2, 2, 0.75);
    }
}

void Link::drawMountingPtAxes()
{
    ci::gl::ScopedGlslProg shader( ci::gl::getStockShader( ci::gl::ShaderDef().color().lambert() ) );
    for ( std::pair<ci::vec3, ci::vec3> line : mountingPoints )
    {
		ci::gl::pushModelMatrix();
		ci::gl::translate(line.first);
		drawCoordinateFrame(10, 2, 2, 0.75);
		ci::gl::popModelMatrix();
	}
}

void Link::drawJointGeomCenterAxes()
{

}

void Link::drawMotorRotationBounds()
{

}

void Link::drawMotorCommandedTorques()
{

}



void Link::drawVector( const ci::vec3& start, const ci::vec3& end, float headLength, float headRadius, float radius )
{
	ci::vec3 dir = end - start;
	ci::vec3 ori = end - normalize( dir ) * headLength;
	ci::gl::draw( ci::geom::Cone().base( headRadius ).height( headLength ).origin( ori ).direction( dir ) );

	ci::gl::draw( ci::geom::Cylinder().origin(start).height(distance(start, ori)).direction( dir ).radius(radius) );
}

void Link::drawCoordinateFrame( float axisLength, float headLength, float headRadius, float shaftRadius )
{
	ci::gl::ScopedColor color( ci::ColorA( 1.0f, 0.0f, 0.0f, 1.0f ) );
	drawVector( ci::vec3( 0.0f ), ci::vec3( 1.0f, 0.0f, 0.0f ) * axisLength, headLength, headRadius, shaftRadius );
	ci::gl::color( 0.0f, 1.0f, 0.0f, 1.0f );
	drawVector( ci::vec3( 0.0f ), ci::vec3( 0.0f, 1.0f, 0.0f ) * axisLength, headLength, headRadius, shaftRadius );
	ci::gl::color( 0.0f, 0.0f, 1.0f, 1.0f );
	drawVector( ci::vec3( 0.0f ), ci::vec3( 0.0f, 0.0f, 1.0f ) * axisLength, headLength, headRadius, shaftRadius );
}
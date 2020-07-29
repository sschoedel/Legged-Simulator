#include "robot_description/Link.h"


void Link::setup(bool _isRoot, float _mass, std::string _name, const ci::geom::Source &shape, ci::gl::GlslProgRef mGlslShadow, ci::vec3 _size, std::vector<std::pair<ci::vec3, ci::vec3>> _mountingPoints, int _thisMountIndex, int _parentMountIndex)
{
	shadowedBatch    = ci::gl::Batch::create(shape, mGlslShadow);
	mainBatch        = ci::gl::Batch::create(shape, ci::gl::getStockShader(ci::gl::ShaderDef()));
	visible          = true;
    isRoot           = _isRoot;
	name             = _name;
	mass             = _mass;
	size             = _size;
	mountingPoints   = _mountingPoints;
	thisMountIndex   = _thisMountIndex;
	parentMountIndex = _parentMountIndex;
	parentIndex		 = 0; // Each link only supports one parent for now

}

void Link::setPoseOffset()
{
	if (!isRoot)
	{
		fprintf(stderr, "\nnum parents: %d", static_cast<int>(parents.size()));
		// poseTransOffset = mountingPoints[thisMountIndex].first - parents[parentIndex].mountingPoints[parentMountIndex].first;
		// ci::vec3 thisRot = mountingPoints[thisMountIndex].second;
		// ci::vec3 parentRot = parents[parentIndex].mountingPoints[parentMountIndex].second;

		// // vector projection of a onto b: a_1 = dot( a, b ) * b / pow( normalize(b), 2 )
		// ci::vec3 x_axis(1,0,0);
		// ci::vec3 y_axis(0,1,0);
		// ci::vec3 z_axis(0,0,1);

		// float thisRot_zy = sqrt( pow(thisRot.z, 2) + pow(thisRot.y, 2) );
		// float thisRot_xz = sqrt( pow(thisRot.x, 2) + pow(thisRot.z, 2) );
		// float thisRot_yx = sqrt( pow(thisRot.y, 2) + pow(thisRot.x, 2) );
		// float parentRot_zy = sqrt( pow(parentRot.z, 2) + pow(parentRot.y, 2) );
		// float parentRot_xz = sqrt( pow(parentRot.x, 2) + pow(parentRot.z, 2) );
		// float parentRot_yx = sqrt( pow(parentRot.y, 2) + pow(parentRot.x, 2) );

		// float poseRotOffsetx = acos( ci::dot( thisRot_zy, parentRot_zy ) );
		// float poseRotOffsety = acos( ci::dot( thisRot_xz, parentRot_xz ) );
		// float poseRotOffsetz = acos( ci::dot( thisRot_yx, parentRot_yx ) );

		// poseOffset = glm::translate ( poseTransOffset )
		// 		   * glm::toMat4 ( glm::angleAxis( poseRotOffsetx, ci::vec3 ( 1, 0, 0 ) ) )
		// 		   * glm::toMat4 ( glm::angleAxis( poseRotOffsety, ci::vec3 ( 0, 1, 0 ) ) )
		// 		   * glm::toMat4 ( glm::angleAxis( poseRotOffsetz, ci::vec3 ( 0, 0, 1 ) ) );
	}
}

void Link::addChild(Link link)
{
	children.push_back(link);
}

void Link::addParent(Link link)
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

#include "Mesh.h"
using namespace ci;
using namespace ci::app;
using namespace std;

MeshRef Mesh::create()
{
	MeshRef ref = std::make_shared<Mesh>();
	return ref;
}

void Mesh::setup(const ci::geom::Source &source,  ci::vec3 pos, ci::Color color, ci::gl::GlslProgRef mGlslShadow)
{

	mPos = pos;
	mColor = color;
	mainBatch = gl::Batch::create(source, gl::getStockShader(gl::ShaderDef()));
	shadowedBatch= gl::Batch::create(source, mGlslShadow);

}
void Mesh::draw() 
{

	gl::color(mColor);
	gl::pushMatrices();
	gl::translate(mPos);
	mainBatch->draw();
	gl::popMatrices();
}
void Mesh::drawShadow() 
{
	gl::pushMatrices();
	gl::translate(mPos);
	shadowedBatch->draw();
	gl::popMatrices();
}


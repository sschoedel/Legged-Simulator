#include "Scene.h"

Scene::Scene()
{
    showFloor = true;
    fboSize = 2048;
    showFloor = true;
}

void Scene::setup()
{
	ci::gl::Texture2d::Format depthFormat;
	depthFormat.setInternalFormat( GL_DEPTH_COMPONENT32F );
	depthFormat.setCompareMode( GL_COMPARE_REF_TO_TEXTURE );
	depthFormat.setMagFilter( GL_LINEAR );
	depthFormat.setMinFilter( GL_LINEAR );
	depthFormat.setWrap( GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE );	
	depthFormat.setCompareFunc( GL_LEQUAL );
	mShadowMapTex = ci::gl::Texture2d::create( fboSize, fboSize, depthFormat );

	try {	
		ci::gl::Fbo::Format fboFormat;
		fboFormat.attachment( GL_DEPTH_ATTACHMENT, mShadowMapTex );
		mFbo = ci::gl::Fbo::create( fboSize, fboSize, fboFormat );
	}
	catch( const std::exception& e ) {
		ci::app::console() << "FBO ERROR: " << e.what() << std::endl;
	}

	mLightPos = ci::vec3(500.0f, 1000.0f, 0.0f);
		
	mLightCam.setPerspective(60.0f, mFbo->getAspectRatio(), 10.f, 2000.0f);
	mLightCam.lookAt(mLightPos, ci::vec3(0.0f));

	try {
		mGlslShadow = ci::gl::GlslProg::create( ci::app::loadAsset("shadow_shader.vert"), ci::app::loadAsset("shadow_shader.frag"));
	}
	catch ( ci::Exception &exc ) {
		CI_LOG_EXCEPTION( "mGlslShadow load failed", exc );
		std::terminate();
	}
	
	try {
		mGlslShadowFloor = ci::gl::GlslProg::create(ci::app::loadAsset("../assets/shadow_shader_floor.vert"), ci::app::loadAsset("../assets/shadow_shader_floor.frag"));
	}
	catch ( ci::Exception &exc ) {
		CI_LOG_EXCEPTION( "mGlslShadowFloor load failed", exc );
		std::terminate();
	}

    floor->setup(ci::geom::Plane().size(ci::vec2(10000,10000)), ci::vec3(0, 0, 0), ci::Color(0.8,0.8,0.82), mGlslShadowFloor);

	// auto shape			= ci::geom::Capsule().radius(35).length(100).direction(ci::vec3(1, 0, 0));
	// mainBatch			= ci::gl::Batch::create( shape, ci::gl::getStockShader( ci::gl::ShaderDef() ));
	// shadowedBatch		= ci::gl::Batch::create( shape, mGlslShadow);
}


// // TODO: remove?
// void Scene::setPart(Link &parent)
// {
// 	Part newPart;
// 	newPart.pColor = parent.pColor;
// 	float tx = parent.centerPos.x;
// 	float ty = parent.centerPos.y;
// 	float tz = parent.centerPos.z;
// 	float rotx = parent.centerRot.x;
// 	float roty = parent.centerRot.y;
// 	float rotz = parent.centerRot.z;
// 	newPart.setPartPose(tx, ty, tz, rotx, roty, rotz, 1);
// 	newPart.mainBatch = parent.mainBatch;
// 	newPart.shadowedBatch = parent.shadowedBatch;

// 	parts.push_back(newPart);
	
// 	for (Link child : parent.children)
// 	{
// 		setPart(child);
// 	}
// }

void Scene::drawModelMain(Link &parent)
{
	// fprintf(stderr, "\n numParts: %d", static_cast<int>(parts.size()));

	// Set polygon offset to battle shadow acne
	ci::gl::enable( GL_POLYGON_OFFSET_FILL );
	glPolygonOffset( 2.0f, 2.0f );

	// Render scene to fbo from the view of the light
	ci::gl::ScopedFramebuffer fbo( mFbo );
	ci::gl::ScopedViewport viewport( ci::vec2( 0.0f ), mFbo->getSize() );
	ci::gl::clear();
	ci::gl::setMatrices( mLightCam );

    updateModelShadows();

    // Draw physical parts here
	drawPart(parent, false);
	
	// Disable polygon offset for final render
	ci::gl::disable( GL_POLYGON_OFFSET_FILL );
}

void Scene::drawModelShadows(Link &parent)
{
    // Set view to viewing camera angle
	ci::gl::setMatrices( camera.mCam );

    //Draw part shadows here
    drawPart(parent, true);
}

// void Scene::drawPart(ci::gl::BatchRef batch, glm::mat4 partPose, ci::Color pColor)
void Scene::drawPart(Link &parent, bool shadow)
{
	// TODO: draw chains within the same pushModelMatrix (pushModelMatrix, Multmodelmatrix, drawlink1, multmodelmatrix, drawlink2, ..., popModelMatrix)
	ci::gl::pushModelMatrix();
	ci::gl::color( parent.pColor );
    ci::gl::multModelMatrix( parent.pose );
	if (shadow)
		parent.shadowedBatch->draw();
		// fprintf(stderr, "\n shadowed");}
	else
		parent.mainBatch->draw();	
		// fprintf(stderr, "\n main");}
		
	ci::gl::popModelMatrix();

	if (shadow)
		for (Link child : parent.children)
		{
			drawPart(child, shadow);
		}
	else
		for (Link child : parent.children)
		{
			drawPart(child, shadow);
		}
}


void Scene::drawFloor()
{
    updateFloorShadows();
	if (showFloor)
	{
		floor->drawShadow();
	}
}

void Scene::updateFloorShadows()
{
    mGlslShadowFloor->uniform("uShadowMap", 0);
	mGlslShadowFloor->uniform("uLightPos", mvLightPos);
	mGlslShadowFloor->uniform("uShadowMatrix", shadowMatrix);
    mGlslShadowFloor->uniform("alpha", 1.f);
}

void Scene::updateModelShadows()
{
    mvLightPos	= ci::vec3( ci::gl::getModelView() * ci::vec4( mLightPos, 1.0f ) ) ;
	shadowMatrix = mLightCam.getProjectionMatrix() * mLightCam.getViewMatrix();

	mGlslShadow->uniform( "uShadowMap", 0 );
	mGlslShadow->uniform( "uLightPos", mvLightPos );
	mGlslShadow->uniform( "uShadowMatrix", shadowMatrix );
}

Part::Part()
{
    pColor = ci::Color(0.2f, 0.7f, 0.5f);
}

void Part::setPartPose(float tx, float ty, float tz, float rotx, float roty, float rotz, float scale)
{
    partPose = glm::translate ( ci::vec3 ( tx, ty, tz ) )
             * glm::toMat4 ( glm::angleAxis( rotx, ci::vec3 ( 1, 0, 0 ) ) )
             * glm::toMat4 ( glm::angleAxis( roty, ci::vec3 ( 0, 1, 0 ) ) )
             * glm::toMat4 ( glm::angleAxis( rotz, ci::vec3 ( 0, 0, 1 ) ) )
             * glm::scale ( ci::vec3 ( scale, scale, scale ) );
}

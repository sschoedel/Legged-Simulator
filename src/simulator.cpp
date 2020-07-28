#include "simulator.h"


void SimulationApp::setup()
{
	setWindowSize(2650, 1920);
	setWindowPos(0, 0);
	gl::enableVerticalSync();
	setFrameRate(30);

	scene.camera.setup();
	scene.setup();
	bot.setup(scene.mGlslShadow);

	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void SimulationApp::update()
{
	// Store time so each render pass uses the same value

	gui.updateCameraGUI(scene.camera);
	gui.updateCamera(scene.camera);
	gui.updateScene(scene);
    gui.updateRobotControl(bot);
    gui.updateRobotConfig(bot);

	// TODO: calculate forces
	// TODO: update kinematics

	// transfer render data to scene
	// scene.setPart(bot.root);
}

void SimulationApp::draw()
{
	gl::clear( Color(0.9f, 0.7f, 0.7f) );
	ci::gl::ScopedTextureBind texScope( scene.mShadowMapTex, (uint8_t) 0 );
	scene.drawModelMain(bot.root);
	scene.drawModelShadows(bot.root);
	scene.drawFloor();
}

CINDER_APP( SimulationApp, RendererGl(RendererGl::Options().msaa(16)))

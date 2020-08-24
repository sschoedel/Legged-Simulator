#include "simulator.h"


void SimulationApp::setup()
{
	scene.setup();
	
	setWindowSize(2650, 1920);
	setWindowPos(0, 0);
	gl::enableVerticalSync();
	setFrameRate(scene.framesPerSecond);

	scene.camera.setCam();
	bot.setup(scene.getPartShadow());

	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void SimulationApp::update()
{
	// Store time so each render pass uses the same value
	mTime = getElapsedSeconds();

	gui.updateScene(scene, bot);
    gui.updateRobotControl(bot);
    gui.updateRobotConfig(bot);

	bot.calcPoses(bot.body);
	bot.calculateTorques(bot.body); // inverse dynamics
	bot.applyTorques(bot.body); // animate links
	// TODO: add ragdoll physics to this - all link forces are nonlinear
}

void SimulationApp::draw()
{
	gl::clear( Color(0.4f, 0.4f, 0.6f) );
	ci::gl::ScopedTextureBind texScope( scene.getShadowMapTex(), (uint8_t) 0 );
	scene.drawModelMain(bot.body);
	scene.drawModelShadows(bot.body);
	bot.visualization();
	scene.drawFloor();
}

CINDER_APP( SimulationApp, RendererGl(RendererGl::Options().msaa(16)))

#include "simulator.h"


void SimulationApp::setup()
{
	setWindowSize(2650, 1920);
	setWindowPos(0, 0);
	gl::enableVerticalSync();
	setFrameRate(30);

	scene.camera.setCam();
	scene.setup();
	bot.setup(scene.getPartShadow());

	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void SimulationApp::update()
{
	// Store time so each render pass uses the same value

	// gui.updateCameraGUI(scene.camera);
	// gui.updateCamera(scene.camera);
	gui.updateScene(scene, bot);
    gui.updateRobotControl(bot);
    gui.updateRobotConfig(bot);

	// scene.setPart(bot.body);
	bot.setChildren();
	bot.calcPoses(bot.body);
	// bot.calcPoses(bot.body.children[0]);
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

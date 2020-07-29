#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/Shader.h"
#include "cinder/gl/Fbo.h"
#include "cinder/TriMesh.h"
#include "cinder/Log.h"

#include "gui.h"
#include "Robot.h"
#include "Camera.h"
#include "Scene.h"
#include "Mesh.h"
#include "MeshPool.h"

using namespace ci;
using namespace ci::app;
using namespace std;

// class SimulationApp : public App {
class SimulationApp : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;

private:
	Robot					bot;// = Robot::create();
	Gui 					gui;
	Scene					scene;

	float mTime;
};


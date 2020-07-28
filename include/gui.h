#pragma once

#include "cinder/CinderImGui.h"
#include "cinder/CameraUi.h"
#include "Camera.h"
#include "Scene.h"
#include "Robot.h"

class Gui
{
    public:
        Gui();
        void updateRobotControl(Robot &robot);
        void updateRobotConfig(Robot &robot);
        void updateScene(Scene &scene);
        void updateCameraGUI(Cam &camera);
        void updateCamera(Cam &camera);
};
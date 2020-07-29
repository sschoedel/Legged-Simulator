#pragma once

#include "cinder/CameraUi.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

class Cam
{
    public:
        Cam() {};
        void setCam();
	    ci::CameraPersp	mCam;
	    ci::CameraUi	mCamUi;
        
        float cameraDistance = 400;
        float cameraTheta = 1.041;
        float cameraPhi = 0.940;
        float yOff = 0;
};
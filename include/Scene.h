#pragma once

#include "Mesh.h"
#include "Camera.h"
#include "Robot.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Batch.h"
#include "cinder/gl/Shader.h"
#include "cinder/gl/Fbo.h"
#include "cinder/Log.h"
#include <vector>

class Part;

class Scene
{
    public:
        Scene();
        void setup();
        // void setPart(Link &parent);
        // void clearParts(Link &parent);

        void drawFloor();
        void drawModelMain(Link &parent);
        void drawModelShadows(Link &parent);
        void drawPart(Link &parent, bool shadow);

        void updateFloorShadows();
        void updateModelShadows();

        bool                    showFloor;

	    Cam						camera;
        ci::gl::Texture2dRef	mShadowMapTex;
	    ci::gl::GlslProgRef		mGlslShadow;

    private:
        int	                    fboSize;
        bool                    shadowMap;

        ci::vec3                mvLightPos;
        ci::CameraPersp			mLightCam;
        ci::vec3				mLightPos;

        ci::mat4                shadowMatrix;
        ci::gl::FboRef			mFbo;
	    ci::gl::GlslProgRef     mGlslShadowFloor;

        MeshRef                 floor = Mesh::create();
        // std::vector<Part>       parts;
};

// Subclass Part for scene because drawing must be part agnostic
// All parts are converted to Part and added to the parts vector before drawing
class Part : public Scene
{
    public:
        Part();
        void setPartPose(float tx, float ty, float tz, float rotx, float roty, float rotz, float scale);

        ci::Color           pColor;
        glm::mat4           partPose;
        ci::gl::BatchRef    mainBatch;
        ci::gl::BatchRef    shadowedBatch;
};
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
        ci::gl::GlslProgRef getPartShadow();
        ci::gl::Texture2dRef getShadowMapTex();

        void setPart(Link &parent);
        void clearParts();

        void drawPart(ci::gl::BatchRef &batch, glm::mat4 partPose, ci::Color pColor);
        void drawPart(ci::gl::BatchRef &batch);
        void drawPart(Link &parent, bool shadow);
        void drawSerialChainPart(Link &parent, bool shadow);

        void drawFloor();
        void drawModelMain(Link &parent);
        void drawModelShadows(Link &parent);
        void drawModelMain();
        void drawModelShadows();

        void updateFloorShadows();
        void updateModelShadows();

        bool                    showFloor;

	    Cam						camera;

        ci::CameraPersp			mLightCam;
        ci::gl::FboRef			mFbo;
        std::vector<Part>       parts;
        ci::gl::BatchRef    mainBatch;
        ci::gl::BatchRef    shadowedBatch;
    private:
        int	                    fboSize;
        bool                    shadowMap;

        ci::vec3                mvLightPos;
        ci::vec3				mLightPos;

        ci::mat4                shadowMatrix;
        ci::gl::Texture2dRef	mShadowMapTex;
	    ci::gl::GlslProgRef     mGlslShadowFloor;
	    ci::gl::GlslProgRef		mGlslShadow;

        MeshRef                 floor = Mesh::create();
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
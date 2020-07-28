#include "Camera.h"

void Cam::setup()
{
	float x = cameraDistance * sinf(cameraTheta) * cosf(cameraPhi);
	float z = cameraDistance * sinf(cameraTheta) * sinf(cameraPhi);
	float y = cameraDistance * cosf(cameraTheta);

	mCam.lookAt(glm::vec3(x, y+yOff, z), glm::vec3(0, yOff,0));
	mCam.setPerspective(30, ci::app::getWindowAspectRatio(), 100, 4000);
}
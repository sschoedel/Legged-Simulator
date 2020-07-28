#pragma once

// #include "glm::vec3.h"
#include "cinder/gl/gl.h"

class ModelConfig 
{
public: 
	bool isDirty = true;

	float homeDistance = 100;

	float upperLegSize = 80;
	float lowerLegSize = 130;
	


	float stepHeight =30;
	int stepPower =3;
	float stepTime = 1.f;


	float frontLegAngle =3.1415/4 ;
	glm::vec3 frontLegStart = glm::vec3(70, 0, 50);

	float middleLegAngle = 0;
	glm::vec3 middleLegStart = glm::vec3(0, 0, 70);

	float backLegAngle = -3.1415 / 4;
	glm::vec3 backLegStart = glm::vec3(-70, 0, 50);
};
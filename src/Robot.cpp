#include "Robot.h"

void Robot::setup(ci::gl::GlslProgRef mGlslShadow)
{
	// TODO: extract all of this information from a URDF or similar definition file

	// root
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt1, rootConfig.mtDir1));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt2, rootConfig.mtDir2));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt3, rootConfig.mtDir3));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt4, rootConfig.mtDir4));
	body->setup(true, rootConfig.rootMass, "root", rootConfig.rootShape, mGlslShadow, rootConfig.size, rootConfig.mountingPoints, -1, -1, rootConfig.rootColor, 0,0,0,0); // -1 because root doesn't have parent links
	// set initial position and rotation for body
	body->jointPoseTrans = rootConfig.initialrootPos;


	// TODO: Left and right sides of shoulders and legs will be different
	// shoulders
	int FLS_parentMountIndex = 0;
	int FRS_parentMountIndex = 1;
	int BLS_parentMountIndex = 2;
	int BRS_parentMountIndex = 3;
	frontLeftShoulderConfig.mountingPoints.push_back(std::make_pair(frontLeftShoulderConfig.mtPt1, frontLeftShoulderConfig.mtDir1));
	frontLeftShoulderConfig.mountingPoints.push_back(std::make_pair(frontLeftShoulderConfig.mtPt2, frontLeftShoulderConfig.mtDir2));
	frontRightShoulderConfig.mountingPoints.push_back(std::make_pair(frontRightShoulderConfig.mtPt1, frontRightShoulderConfig.mtDir1));
	frontRightShoulderConfig.mountingPoints.push_back(std::make_pair(frontRightShoulderConfig.mtPt2, frontRightShoulderConfig.mtDir2));
	backLeftShoulderConfig.mountingPoints.push_back(std::make_pair(backLeftShoulderConfig.mtPt1, backLeftShoulderConfig.mtDir1));
	backLeftShoulderConfig.mountingPoints.push_back(std::make_pair(backLeftShoulderConfig.mtPt2, backLeftShoulderConfig.mtDir2));
	backRightShoulderConfig.mountingPoints.push_back(std::make_pair(backRightShoulderConfig.mtPt1, backRightShoulderConfig.mtDir1));
	backRightShoulderConfig.mountingPoints.push_back(std::make_pair(backRightShoulderConfig.mtPt2, backRightShoulderConfig.mtDir2));
	FLS->setup(false, frontLeftShoulderConfig.mass, "FLS", frontLeftShoulderConfig.shoulderShape, mGlslShadow, frontLeftShoulderConfig.size, frontLeftShoulderConfig.mountingPoints,
			   frontLeftShoulderConfig.thisMountIndex, FLS_parentMountIndex, frontLeftShoulderConfig.color, frontLeftShoulderConfig.zeroJointAngle, frontLeftShoulderConfig.initialJointAngle, frontLeftShoulderConfig.rotationDirection, frontLeftShoulderConfig.rotationAxis);
	FRS->setup(false, frontRightShoulderConfig.mass, "FRS", frontRightShoulderConfig.shoulderShape, mGlslShadow, frontRightShoulderConfig.size, frontRightShoulderConfig.mountingPoints,
			   frontRightShoulderConfig.thisMountIndex, FRS_parentMountIndex, frontRightShoulderConfig.color, frontRightShoulderConfig.zeroJointAngle, frontRightShoulderConfig.initialJointAngle, frontRightShoulderConfig.rotationDirection, frontRightShoulderConfig.rotationAxis);
	BLS->setup(false, backLeftShoulderConfig.mass, "BLS", backLeftShoulderConfig.shoulderShape, mGlslShadow, backLeftShoulderConfig.size, backLeftShoulderConfig.mountingPoints,
			   backLeftShoulderConfig.thisMountIndex, BLS_parentMountIndex, backLeftShoulderConfig.color, backLeftShoulderConfig.zeroJointAngle, backLeftShoulderConfig.initialJointAngle, backLeftShoulderConfig.rotationDirection, backLeftShoulderConfig.rotationAxis);
	BRS->setup(false, backRightShoulderConfig.mass, "BRS", backRightShoulderConfig.shoulderShape, mGlslShadow, backRightShoulderConfig.size, backRightShoulderConfig.mountingPoints,
			   backRightShoulderConfig.thisMountIndex, BRS_parentMountIndex, backRightShoulderConfig.color, backRightShoulderConfig.zeroJointAngle, backRightShoulderConfig.initialJointAngle, backRightShoulderConfig.rotationDirection, backRightShoulderConfig.rotationAxis);

	// leg upper
	frontLeftUpperLegConfig.mountingPoints.push_back(std::make_pair(frontLeftUpperLegConfig.mtPt1, frontLeftUpperLegConfig.mtDir1));
	frontLeftUpperLegConfig.mountingPoints.push_back(std::make_pair(frontLeftUpperLegConfig.mtPt2, frontLeftUpperLegConfig.mtDir2));
	frontRightUpperLegConfig.mountingPoints.push_back(std::make_pair(frontRightUpperLegConfig.mtPt1, frontRightUpperLegConfig.mtDir1));
	frontRightUpperLegConfig.mountingPoints.push_back(std::make_pair(frontRightUpperLegConfig.mtPt2, frontRightUpperLegConfig.mtDir2));
	backLeftUpperLegConfig.mountingPoints.push_back(std::make_pair(backLeftUpperLegConfig.mtPt1, backLeftUpperLegConfig.mtDir1));
	backLeftUpperLegConfig.mountingPoints.push_back(std::make_pair(backLeftUpperLegConfig.mtPt2, backLeftUpperLegConfig.mtDir2));
	backRightUpperLegConfig.mountingPoints.push_back(std::make_pair(backRightUpperLegConfig.mtPt1, backRightUpperLegConfig.mtDir1));
	backRightUpperLegConfig.mountingPoints.push_back(std::make_pair(backRightUpperLegConfig.mtPt2, backRightUpperLegConfig.mtDir2));
	FLU->setup(false, frontLeftUpperLegConfig.mass, "FLU", frontLeftUpperLegConfig.upperLegShape, mGlslShadow, frontLeftUpperLegConfig.size, frontLeftUpperLegConfig.mountingPoints,
			   frontLeftUpperLegConfig.thisMountIndex, frontLeftUpperLegConfig.parentMountIndex, frontLeftUpperLegConfig.color, frontLeftUpperLegConfig.zeroJointAngle, frontLeftUpperLegConfig.initialJointAngle, frontLeftUpperLegConfig.rotationDirection, frontLeftUpperLegConfig.rotationAxis);
	FRU->setup(false, frontRightUpperLegConfig.mass, "FRU", frontRightUpperLegConfig.upperLegShape, mGlslShadow, frontRightUpperLegConfig.size, frontRightUpperLegConfig.mountingPoints,
			   frontRightUpperLegConfig.thisMountIndex, frontRightUpperLegConfig.parentMountIndex, frontRightUpperLegConfig.color, frontRightUpperLegConfig.zeroJointAngle, frontRightUpperLegConfig.initialJointAngle, frontRightUpperLegConfig.rotationDirection, frontRightUpperLegConfig.rotationAxis);
	BLU->setup(false, backLeftUpperLegConfig.mass, "BLU", backLeftUpperLegConfig.upperLegShape, mGlslShadow, backLeftUpperLegConfig.size, backLeftUpperLegConfig.mountingPoints,
			   backLeftUpperLegConfig.thisMountIndex, backLeftUpperLegConfig.parentMountIndex, backLeftUpperLegConfig.color, backLeftUpperLegConfig.zeroJointAngle, backLeftUpperLegConfig.initialJointAngle, backLeftUpperLegConfig.rotationDirection, backLeftUpperLegConfig.rotationAxis);
	BRU->setup(false, backRightUpperLegConfig.mass, "BRU", backRightUpperLegConfig.upperLegShape, mGlslShadow, backRightUpperLegConfig.size, backRightUpperLegConfig.mountingPoints,
			   backRightUpperLegConfig.thisMountIndex, backRightUpperLegConfig.parentMountIndex, backRightUpperLegConfig.color, backRightUpperLegConfig.zeroJointAngle, backRightUpperLegConfig.initialJointAngle, backRightUpperLegConfig.rotationDirection, backRightUpperLegConfig.rotationAxis);

	// leg lower
	frontLeftLowerLegConfig.mountingPoints.push_back(std::make_pair(frontLeftLowerLegConfig.mtPt1, frontLeftLowerLegConfig.mtDir1));
	frontLeftLowerLegConfig.mountingPoints.push_back(std::make_pair(frontLeftLowerLegConfig.mtPt2, frontLeftLowerLegConfig.mtDir2));
	frontRightLowerLegConfig.mountingPoints.push_back(std::make_pair(frontRightLowerLegConfig.mtPt1, frontRightLowerLegConfig.mtDir1));
	frontRightLowerLegConfig.mountingPoints.push_back(std::make_pair(frontRightLowerLegConfig.mtPt2, frontRightLowerLegConfig.mtDir2));
	backLeftLowerLegConfig.mountingPoints.push_back(std::make_pair(backLeftLowerLegConfig.mtPt1, backLeftLowerLegConfig.mtDir1));
	backLeftLowerLegConfig.mountingPoints.push_back(std::make_pair(backLeftLowerLegConfig.mtPt2, backLeftLowerLegConfig.mtDir2));
	backRightLowerLegConfig.mountingPoints.push_back(std::make_pair(backRightLowerLegConfig.mtPt1, backRightLowerLegConfig.mtDir1));
	backRightLowerLegConfig.mountingPoints.push_back(std::make_pair(backRightLowerLegConfig.mtPt2, backRightLowerLegConfig.mtDir2));
	FLL->setup(false, frontLeftLowerLegConfig.mass, "FLL", frontLeftLowerLegConfig.lowerLegShape, mGlslShadow, frontLeftLowerLegConfig.size, frontLeftLowerLegConfig.mountingPoints,
			   frontLeftLowerLegConfig.thisMountIndex, frontLeftLowerLegConfig.parentMountIndex, frontLeftLowerLegConfig.color, frontLeftLowerLegConfig.zeroJointAngle, frontLeftLowerLegConfig.initialJointAngle, frontLeftLowerLegConfig.rotationDirection, frontLeftLowerLegConfig.rotationAxis);
	FRL->setup(false, frontRightLowerLegConfig.mass, "FRL", frontRightLowerLegConfig.lowerLegShape, mGlslShadow, frontRightLowerLegConfig.size, frontRightLowerLegConfig.mountingPoints,
			   frontRightLowerLegConfig.thisMountIndex, frontRightLowerLegConfig.parentMountIndex, frontRightLowerLegConfig.color, frontRightLowerLegConfig.zeroJointAngle, frontRightLowerLegConfig.initialJointAngle, frontRightLowerLegConfig.rotationDirection, frontRightLowerLegConfig.rotationAxis);
	BLL->setup(false, backLeftLowerLegConfig.mass, "BLL", backLeftLowerLegConfig.lowerLegShape, mGlslShadow, backLeftLowerLegConfig.size, backLeftLowerLegConfig.mountingPoints,
			   backLeftLowerLegConfig.thisMountIndex, backLeftLowerLegConfig.parentMountIndex, backLeftLowerLegConfig.color, backLeftLowerLegConfig.zeroJointAngle, backLeftLowerLegConfig.initialJointAngle, backLeftLowerLegConfig.rotationDirection, backLeftLowerLegConfig.rotationAxis);
	BRL->setup(false, backRightLowerLegConfig.mass, "BRL", backRightLowerLegConfig.lowerLegShape, mGlslShadow, backRightLowerLegConfig.size, backRightLowerLegConfig.mountingPoints,
			   backRightLowerLegConfig.thisMountIndex, backRightLowerLegConfig.parentMountIndex, backRightLowerLegConfig.color, backRightLowerLegConfig.zeroJointAngle, backRightLowerLegConfig.initialJointAngle, backRightLowerLegConfig.rotationDirection, backRightLowerLegConfig.rotationAxis);

	setChildren();
	
	FLS->setPoses();
	FRS->setPoses();
	BLS->setPoses();
	BRS->setPoses();
	FLL->setPoses();
	FRL->setPoses();
	BLL->setPoses();
	BRL->setPoses();
	FLU->setPoses();
	FRU->setPoses();
	BLU->setPoses();
	BRU->setPoses();
}

void Robot::setChildren()
{
	clearFamily(body);

	FLU->addChild(FLL);
	FLS->addChild(FLU);
	body->addChild(FLS);

	FLL->addParent(FLU);
	FLU->addParent(FLS);
	FLS->addParent(body);


	FRU->addChild(FRL);
	FRS->addChild(FRU);
	body->addChild(FRS);

	FRL->addParent(FRU);
	FRU->addParent(FRS);
	FRS->addParent(body);


	BLU->addChild(BLL);
	BLS->addChild(BLU);
	body->addChild(BLS);

	BLL->addParent(BLU);
	BLU->addParent(BLS);
	BLS->addParent(body);


	BRU->addChild(BRL);
	BRS->addChild(BRU);
	body->addChild(BRS);

	BRL->addParent(BRU);
	BRU->addParent(BRS);
	BRS->addParent(body);
}

void Robot::clearFamily(LinkRef &parent)
{
	for (LinkRef child : parent->children)
		clearFamily(child);
	parent->clearChildren();
	parent->clearParents();
}

void Robot::calcPoses(LinkRef &parent)
{
	parent->updateJointPose();
	for (int i=0;i<parent->children.size();i++)
		calcPoses(parent->children[i]);
}

glm::mat4 Robot::calcPartPose(float tx, float ty, float tz, float rotx, float roty, float rotz, float scale)
{
    return (   glm::translate ( ci::vec3 ( tx, ty, tz ) )
             * glm::toMat4 ( glm::angleAxis( rotx, ci::vec3 ( 1, 0, 0 ) ) )
             * glm::toMat4 ( glm::angleAxis( roty, ci::vec3 ( 0, 1, 0 ) ) )
             * glm::toMat4 ( glm::angleAxis( rotz, ci::vec3 ( 0, 0, 1 ) ) )
             * glm::scale ( ci::vec3 ( scale, scale, scale ) )
	);
}

void Robot::visualization()
{
	if ( showMtPtLines || showMtPtAxes || showLinkAxes || showFullRotation || showMotorTorques || showCurrentRotations )
	{
		ci::gl::pushModelMatrix();
		std::vector<glm::mat4> prevPoses;
		visualizePartVars(body, prevPoses);
		ci::gl::popModelMatrix();
	}
}

void Robot::visualizePartVars(LinkRef &parent, std::vector<glm::mat4> prevPoses)
{
	ci::gl::multModelMatrix(parent->jointPose);
	ci::gl::multModelMatrix(parent->linkPose);

	if (showMtPtLines)    		{ parent->drawMountingPtLines(); 	   }
	if (showMtPtAxes)     		{ parent->drawMountingPtAxes(); 	   }
	if (showLinkAxes)     		{ parent->drawJointGeomCenterAxes();   }
	if (showFullRotation) 		{ parent->drawMotorRotationBounds();   }
	if (showCurrentRotations) 	{ parent->drawMotorRotations(); 	   }
	if (showMotorTorques) 		{ parent->drawMotorCommandedTorques(); }
	
	for (LinkRef child : parent->children)
	{
		ci::gl::pushModelMatrix();
		visualizePartVars(child, prevPoses);
		ci::gl::popModelMatrix();
	}
}

void Robot::calculateTorques(LinkRef &parent)
{
	parent->torqueOnJoint = 5; // in Nm
	
	for (LinkRef child : parent->children)
		applyTorques(child);
}

void Robot::applyTorques(LinkRef &parent)
{
	parent->jointAngle += parent->torqueOnJoint/parent->mass; // TODO: change mass to inertia for given link

	for (LinkRef child : parent->children)
		applyTorques(child);
}
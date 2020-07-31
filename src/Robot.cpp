#include "Robot.h"

void Robot::setup(ci::gl::GlslProgRef mGlslShadow)
{
	// TODO: extract all of this information from a URDF or similar definition file

	// root
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt1, rootConfig.mtDir1));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt2, rootConfig.mtDir2));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt3, rootConfig.mtDir3));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt4, rootConfig.mtDir4));
	body->setup(true, rootConfig.rootMass, "root", rootConfig.rootShape, mGlslShadow, rootConfig.size, rootConfig.mountingPoints, -1, -1, rootConfig.rootColor, 0,0,0); // -1 because root doesn't have parent links
	// set initial position and rotation for body
	body->jointPoseTrans = rootConfig.initialrootPos;
	body->jointPoseRot   = rootConfig.initialrootRot;


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
			   frontLeftShoulderConfig.thisMountIndex, FLS_parentMountIndex, frontLeftShoulderConfig.color, frontLeftShoulderConfig.zeroJointAngle, frontLeftShoulderConfig.rotationDirection, frontLeftShoulderConfig.rotationAxis);
	FRS->setup(false, frontRightShoulderConfig.mass, "FRS", frontRightShoulderConfig.shoulderShape, mGlslShadow, frontRightShoulderConfig.size, frontRightShoulderConfig.mountingPoints,
			   frontRightShoulderConfig.thisMountIndex, FRS_parentMountIndex, frontRightShoulderConfig.color, frontRightShoulderConfig.zeroJointAngle, frontRightShoulderConfig.rotationDirection, frontRightShoulderConfig.rotationAxis);
	BLS->setup(false, backLeftShoulderConfig.mass, "BLS", backLeftShoulderConfig.shoulderShape, mGlslShadow, backLeftShoulderConfig.size, backLeftShoulderConfig.mountingPoints,
			   backLeftShoulderConfig.thisMountIndex, BLS_parentMountIndex, backLeftShoulderConfig.color, backLeftShoulderConfig.zeroJointAngle, backLeftShoulderConfig.rotationDirection, backLeftShoulderConfig.rotationAxis);
	BRS->setup(false, backRightShoulderConfig.mass, "BRS", backRightShoulderConfig.shoulderShape, mGlslShadow, backRightShoulderConfig.size, backRightShoulderConfig.mountingPoints,
			   backRightShoulderConfig.thisMountIndex, BRS_parentMountIndex, backRightShoulderConfig.color, backRightShoulderConfig.zeroJointAngle, backRightShoulderConfig.rotationDirection, backRightShoulderConfig.rotationAxis);

	// leg upper
	leftUpperLegConfig.mountingPoints.push_back(std::make_pair(leftUpperLegConfig.mtPt1, leftUpperLegConfig.mtDir1));
	leftUpperLegConfig.mountingPoints.push_back(std::make_pair(leftUpperLegConfig.mtPt2, leftUpperLegConfig.mtDir2));
	rightUpperLegConfig.mountingPoints.push_back(std::make_pair(rightUpperLegConfig.mtPt1, rightUpperLegConfig.mtDir1));
	rightUpperLegConfig.mountingPoints.push_back(std::make_pair(rightUpperLegConfig.mtPt2, rightUpperLegConfig.mtDir2));
	FLU->setup(false, leftUpperLegConfig.mass, "FLU", leftUpperLegConfig.upperLegShape, mGlslShadow, leftUpperLegConfig.size, leftUpperLegConfig.mountingPoints,
			   leftUpperLegConfig.thisMountIndex, leftUpperLegConfig.parentMountIndex, leftUpperLegConfig.color, leftUpperLegConfig.zeroJointAngle, leftUpperLegConfig.rotationDirection, leftUpperLegConfig.rotationAxis);
	FRU->setup(false, rightUpperLegConfig.mass, "FRU", rightUpperLegConfig.upperLegShape, mGlslShadow, rightUpperLegConfig.size, rightUpperLegConfig.mountingPoints,
			   rightUpperLegConfig.thisMountIndex, rightUpperLegConfig.parentMountIndex, rightUpperLegConfig.color, rightUpperLegConfig.zeroJointAngle, rightUpperLegConfig.rotationDirection, rightUpperLegConfig.rotationAxis);
	BLU->setup(false, leftUpperLegConfig.mass, "BLU", leftUpperLegConfig.upperLegShape, mGlslShadow, leftUpperLegConfig.size, leftUpperLegConfig.mountingPoints,
			   leftUpperLegConfig.thisMountIndex, leftUpperLegConfig.parentMountIndex, leftUpperLegConfig.color, leftUpperLegConfig.zeroJointAngle, leftUpperLegConfig.rotationDirection, leftUpperLegConfig.rotationAxis);
	BRU->setup(false, rightUpperLegConfig.mass, "BRU", rightUpperLegConfig.upperLegShape, mGlslShadow, rightUpperLegConfig.size, rightUpperLegConfig.mountingPoints,
			   rightUpperLegConfig.thisMountIndex, rightUpperLegConfig.parentMountIndex, rightUpperLegConfig.color, rightUpperLegConfig.zeroJointAngle, rightUpperLegConfig.rotationDirection, rightUpperLegConfig.rotationAxis);

	// leg lower
	leftLowerLegConfig.mountingPoints.push_back(std::make_pair(leftLowerLegConfig.mtPt1, leftLowerLegConfig.mtDir1));
	leftLowerLegConfig.mountingPoints.push_back(std::make_pair(leftLowerLegConfig.mtPt2, leftLowerLegConfig.mtDir2));
	rightLowerLegConfig.mountingPoints.push_back(std::make_pair(rightLowerLegConfig.mtPt1, rightLowerLegConfig.mtDir1));
	rightLowerLegConfig.mountingPoints.push_back(std::make_pair(rightLowerLegConfig.mtPt2, rightLowerLegConfig.mtDir2));
	FLL->setup(false, leftLowerLegConfig.mass, "FLL", leftLowerLegConfig.lowerLegShape, mGlslShadow, leftLowerLegConfig.size, leftLowerLegConfig.mountingPoints,
			   leftLowerLegConfig.thisMountIndex, leftLowerLegConfig.parentMountIndex, leftLowerLegConfig.color, leftLowerLegConfig.zeroJointAngle, leftLowerLegConfig.rotationDirection, leftLowerLegConfig.rotationAxis);
	FRL->setup(false, rightLowerLegConfig.mass, "FRL", rightLowerLegConfig.lowerLegShape, mGlslShadow, rightLowerLegConfig.size, rightLowerLegConfig.mountingPoints,
			   rightLowerLegConfig.thisMountIndex, rightLowerLegConfig.parentMountIndex, rightLowerLegConfig.color, rightLowerLegConfig.zeroJointAngle, rightLowerLegConfig.rotationDirection, rightLowerLegConfig.rotationAxis);
	BLL->setup(false, leftLowerLegConfig.mass, "BLL", leftLowerLegConfig.lowerLegShape, mGlslShadow, leftLowerLegConfig.size, leftLowerLegConfig.mountingPoints,
			   leftLowerLegConfig.thisMountIndex, leftLowerLegConfig.parentMountIndex, leftLowerLegConfig.color, leftLowerLegConfig.zeroJointAngle, leftLowerLegConfig.rotationDirection, leftLowerLegConfig.rotationAxis);
	BRL->setup(false, rightLowerLegConfig.mass, "BRL", rightLowerLegConfig.lowerLegShape, mGlslShadow, rightLowerLegConfig.size, rightLowerLegConfig.mountingPoints,
			   rightLowerLegConfig.thisMountIndex, rightLowerLegConfig.parentMountIndex, rightLowerLegConfig.color, rightLowerLegConfig.zeroJointAngle, rightLowerLegConfig.rotationDirection, rightLowerLegConfig.rotationAxis);

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
	if ( showMtPtLines || showMtPtAxes || showLinkAxes || showFullRotation || showMotorTorques )
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

	if (showMtPtLines)    { parent->drawMountingPtLines(); }
	if (showMtPtAxes)     { parent->drawMountingPtAxes(); }
	if (showLinkAxes)     { parent->drawJointGeomCenterAxes(); }
	if (showFullRotation) { parent->drawMotorRotationBounds(); }
	if (showMotorTorques) { parent->drawMotorCommandedTorques(); }
	
	for (LinkRef child : parent->children)
	{
		ci::gl::pushModelMatrix();
		visualizePartVars(child, prevPoses);
		ci::gl::popModelMatrix();
	}
}
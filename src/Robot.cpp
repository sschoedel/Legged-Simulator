#include "Robot.h"

void Robot::setup(ci::gl::GlslProgRef mGlslShadow)
{
	// TODO: extract all of this information from a URDF or similar definition file

	// root
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt1, rootConfig.mtDir1));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt3, rootConfig.mtDir3));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt4, rootConfig.mtDir4));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt2, rootConfig.mtDir2));
	body.setup(true, rootConfig.rootMass, "root", rootConfig.rootShape, mGlslShadow, rootConfig.size, rootConfig.mountingPoints, -1, -1); // -1 because root doesn't have parent links
	// set initial position and rotation for body
	body.centerPos = rootConfig.initialrootPos;
	body.centerRot = rootConfig.initialrootRot;
	body.pColor    = rootConfig.rootColor;


	// TODO: Left and right sides of shoulders and legs will be different
	// shoulders
	int FLS_parentMountIndex = 0;
	int FRS_parentMountIndex = 1;
	int BLS_parentMountIndex = 2;
	int BRS_parentMountIndex = 3;
	shoulderConfig.mountingPoints.push_back(std::make_pair(shoulderConfig.mtPt1, shoulderConfig.mtDir1));
	shoulderConfig.mountingPoints.push_back(std::make_pair(shoulderConfig.mtPt2, shoulderConfig.mtDir2));
	FLS.setup(false, shoulderConfig.mass, "FLS", shoulderConfig.shoulderShape, mGlslShadow, shoulderConfig.size, shoulderConfig.mountingPoints, shoulderConfig.thisMountIndex, FLS_parentMountIndex);
	FRS.setup(false, shoulderConfig.mass, "FRS", shoulderConfig.shoulderShape, mGlslShadow, shoulderConfig.size, shoulderConfig.mountingPoints, shoulderConfig.thisMountIndex, FRS_parentMountIndex);
	BLS.setup(false, shoulderConfig.mass, "BLS", shoulderConfig.shoulderShape, mGlslShadow, shoulderConfig.size, shoulderConfig.mountingPoints, shoulderConfig.thisMountIndex, BLS_parentMountIndex);
	BRS.setup(false, shoulderConfig.mass, "BRS", shoulderConfig.shoulderShape, mGlslShadow, shoulderConfig.size, shoulderConfig.mountingPoints, shoulderConfig.thisMountIndex, BRS_parentMountIndex);

	FLS.pColor = shoulderConfig.color;
	FRS.pColor = shoulderConfig.color;
	BLS.pColor = shoulderConfig.color;
	BRS.pColor = shoulderConfig.color;
	FLS.jointAngle = shoulderConfig.initialJointAngle;
	FRS.jointAngle = shoulderConfig.initialJointAngle;
	BLS.jointAngle = shoulderConfig.initialJointAngle;
	BRS.jointAngle = shoulderConfig.initialJointAngle;

	// front left leg upper
	upperLegConfig.mountingPoints.push_back(std::make_pair(upperLegConfig.mtPt1, upperLegConfig.mtDir1));
	upperLegConfig.mountingPoints.push_back(std::make_pair(upperLegConfig.mtPt2, upperLegConfig.mtDir2));
	FLU.setup(false, upperLegConfig.mass, "FLU", upperLegConfig.upperLegShape, mGlslShadow, upperLegConfig.size, upperLegConfig.mountingPoints, upperLegConfig.thisMountIndex, upperLegConfig.parentMountIndex);
	FRU.setup(false, upperLegConfig.mass, "FRU", upperLegConfig.upperLegShape, mGlslShadow, upperLegConfig.size, upperLegConfig.mountingPoints, upperLegConfig.thisMountIndex, upperLegConfig.parentMountIndex);
	BLU.setup(false, upperLegConfig.mass, "BLU", upperLegConfig.upperLegShape, mGlslShadow, upperLegConfig.size, upperLegConfig.mountingPoints, upperLegConfig.thisMountIndex, upperLegConfig.parentMountIndex);
	BRU.setup(false, upperLegConfig.mass, "BRU", upperLegConfig.upperLegShape, mGlslShadow, upperLegConfig.size, upperLegConfig.mountingPoints, upperLegConfig.thisMountIndex, upperLegConfig.parentMountIndex);

	FLU.pColor = upperLegConfig.color;
	FRU.pColor = upperLegConfig.color;
	BLU.pColor = upperLegConfig.color;
	BRU.pColor = upperLegConfig.color;
	FLU.jointAngle = upperLegConfig.initialJointAngle;
	FRU.jointAngle = upperLegConfig.initialJointAngle;
	BLU.jointAngle = upperLegConfig.initialJointAngle;
	BRU.jointAngle = upperLegConfig.initialJointAngle;

	// front left leg lower
	lowerLegConfig.mountingPoints.push_back(std::make_pair(lowerLegConfig.mtPt1, lowerLegConfig.mtDir1));
	lowerLegConfig.mountingPoints.push_back(std::make_pair(lowerLegConfig.mtPt2, lowerLegConfig.mtDir2));
	FLL.setup(false, lowerLegConfig.mass, "FLL", lowerLegConfig.lowerLegShape, mGlslShadow, lowerLegConfig.size, lowerLegConfig.mountingPoints, lowerLegConfig.thisMountIndex, lowerLegConfig.parentMountIndex);
	FRL.setup(false, lowerLegConfig.mass, "FRL", lowerLegConfig.lowerLegShape, mGlslShadow, lowerLegConfig.size, lowerLegConfig.mountingPoints, lowerLegConfig.thisMountIndex, lowerLegConfig.parentMountIndex);
	BLL.setup(false, lowerLegConfig.mass, "BLL", lowerLegConfig.lowerLegShape, mGlslShadow, lowerLegConfig.size, lowerLegConfig.mountingPoints, lowerLegConfig.thisMountIndex, lowerLegConfig.parentMountIndex);
	BRL.setup(false, lowerLegConfig.mass, "BRL", lowerLegConfig.lowerLegShape, mGlslShadow, lowerLegConfig.size, lowerLegConfig.mountingPoints, lowerLegConfig.thisMountIndex, lowerLegConfig.parentMountIndex);

	FLL.pColor = lowerLegConfig.color;
	FRL.pColor = lowerLegConfig.color;
	BLL.pColor = lowerLegConfig.color;
	BRL.pColor = lowerLegConfig.color;
	FLL.jointAngle = lowerLegConfig.initialJointAngle;
	FRL.jointAngle = lowerLegConfig.initialJointAngle;
	BLL.jointAngle = lowerLegConfig.initialJointAngle;
	BRL.jointAngle = lowerLegConfig.initialJointAngle;

	// setChildren();
	
	// FLL.setPoseOffset();
	// FRL.setPoseOffset();
	// BLL.setPoseOffset();
	// BRL.setPoseOffset();
	// FLL.setPoseOffset();
	// FRL.setPoseOffset();
	// BLL.setPoseOffset();
	// BRL.setPoseOffset();

}

void Robot::setChildren()
{
	clearFamily(body);
	// clearFamily(FLS);

	// FLU.addChild(FLL);
	// FLS.addChild(FLU);
	body.addChild(FLS);
	// FLL.addParent(FLU);
	// FLU.addParent(FLS);
	FLS.addParent(body);
	fprintf(stderr, "body child size: %d\n", FLS.parents.size());
	fprintf(stderr, "child names for FLS: \n");
	for (Link parent : body.children)
	{
		std::cout << "child name: " << parent.name << std::endl;
	}

	fprintf(stderr, "FLS parent size: %d\n", FLS.parents.size());
	fprintf(stderr, "parent names for FLS: \n");
	for (Link parent : FLS.parents)
	{
		std::cout << "parent name: " << parent.name << std::endl;
	}
	// FRU.addChild(FRL);
	// FRS.addChild(FRU);
	// body.addChild(FRS);

	// BLU.addChild(BLL);
	// BLS.addChild(BLU);
	// body.addChild(BLS);

	// BRU.addChild(BRL);
	// BRS.addChild(BRU);
	// body.addChild(BRS);
}

void Robot::clearFamily(Link &parent)
{
	if (parent.children.size() == 1)
		clearFamily(parent.children[0]);
	parent.clearChildren();
	parent.clearParents();
	// fprintf(stderr, "\nchildren size: %d, parents size: %d", parent.children.size(), parent.parents.size());
	// for (Link child : parent.children)
	// 	clearFamily(child);
	// std::cout << "name before: " << parent.name << std::endl;
	// for (int i=0;i<parent.children.size();i++)
	// 	clearFamily(parent.children[i]);
	// std::cout << "name after: " << parent.name << std::endl;
	// fprintf(stderr, "parents size before clearing: %d\n", parent.parents.size());
	// fprintf(stderr, "children size before clearing: %d\n", parent.parents.size());
	// // parent.parents.clear();
	// // parent.children.clear();
	// parent.clearChildren();
	// parent.clearParents();
	// fprintf(stderr, "parents size after clearing: %d\n", parent.parents.size());
	// fprintf(stderr, "parents size after clearing: %d\n", parent.parents.size());
}

void Robot::calcPoses(Link &parent)
{
	float tx = parent.centerPos.x;
	float ty = parent.centerPos.y;
	float tz = parent.centerPos.z;
	float rotx = parent.centerRot.x;
	float roty = parent.centerRot.y;
	float rotz = parent.centerRot.z;
	parent.pose = calcPartPose(tx, ty, tz, rotx, roty, rotz, 1);
	for (int i=0;i<parent.children.size();i++)
		calcPoses(parent.children[i]);
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
	if ( showMtPtLines || showMtPtAxes || showJointAxes || showFullRotation || showMotorTorques )
	{
		ci::gl::pushModelMatrix();
		std::vector<glm::mat4> prevPoses;
		visualizePartVars(body, prevPoses);
		ci::gl::popModelMatrix();
	}
}

void Robot::visualizePartVars(Link &parent, std::vector<glm::mat4> prevPoses)
{
	ci::gl::multModelMatrix(parent.pose);

	if (showMtPtLines)    { parent.drawMountingPtLines(); }
	if (showMtPtAxes)     { parent.drawMountingPtAxes(); }
	if (showJointAxes)    { parent.drawJointGeomCenterAxes(); }
	if (showFullRotation) { parent.drawMotorRotationBounds(); }
	if (showMotorTorques) { parent.drawMotorCommandedTorques(); }
	
	for (Link child : parent.children)
		visualizePartVars(child, prevPoses);
	// for (int i=0;i<parent.children.size();i++)
	// 	visualizePartVars(parent.children[i], prevPoses);
}
#include "Robot.h"


void Robot::setup(ci::gl::GlslProgRef mGlslShadow)
{
	// TODO: extract all of this information from a URDF or similar definition file

	// root
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt1, rootConfig.mtDir1));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt3, rootConfig.mtDir3));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt4, rootConfig.mtDir4));
	rootConfig.mountingPoints.push_back(std::make_pair(rootConfig.mtPt2, rootConfig.mtDir2));
	ci::gl::BatchRef	mainBatchroot       = ci::gl::Batch::create(rootConfig.rootShape, mGlslShadow);
	ci::gl::BatchRef	shadowedBatchroot   = ci::gl::Batch::create(rootConfig.rootShape, ci::gl::getStockShader(ci::gl::ShaderDef()));
	root.setup(true, rootConfig.rootMass, "root", mainBatchroot, shadowedBatchroot, rootConfig.size, rootConfig.mountingPoints, -1, -1); // -1 because root doesn't have parent links
	// set initial position and rotation for body
	root.centerPos = rootConfig.initialrootPos;
	root.centerRot = rootConfig.initialrootRot;


	// TODO: Left and right sides of shoulders and legs will be different
	// shoulders
	int FLS_parentMountIndex = 0;
	int FRS_parentMountIndex = 1;
	int BLS_parentMountIndex = 2;
	int BRS_parentMountIndex = 3;
	shoulderConfig.mountingPoints.push_back(std::make_pair(shoulderConfig.mtPt1, shoulderConfig.mtDir1));
	shoulderConfig.mountingPoints.push_back(std::make_pair(shoulderConfig.mtPt2, shoulderConfig.mtDir2));
	ci::gl::BatchRef mainBatchShoulder = ci::gl::Batch::create(shoulderConfig.shoulderShape, mGlslShadow);
	ci::gl::BatchRef shadowedBatchShoulder = ci::gl::Batch::create(shoulderConfig.shoulderShape, ci::gl::getStockShader(ci::gl::ShaderDef()));
	FLS.setup(false, shoulderConfig.mass, "FLS", mainBatchShoulder, shadowedBatchShoulder, shoulderConfig.size, shoulderConfig.mountingPoints, shoulderConfig.thisMountIndex, FLS_parentMountIndex);
	FRS.setup(false, shoulderConfig.mass, "FRS", mainBatchShoulder, shadowedBatchShoulder, shoulderConfig.size, shoulderConfig.mountingPoints, shoulderConfig.thisMountIndex, FRS_parentMountIndex);
	BLS.setup(false, shoulderConfig.mass, "BLS", mainBatchShoulder, shadowedBatchShoulder, shoulderConfig.size, shoulderConfig.mountingPoints, shoulderConfig.thisMountIndex, BLS_parentMountIndex);
	BRS.setup(false, shoulderConfig.mass, "BRS", mainBatchShoulder, shadowedBatchShoulder, shoulderConfig.size, shoulderConfig.mountingPoints, shoulderConfig.thisMountIndex, BRS_parentMountIndex);

	// front left leg upper
	upperLegConfig.mountingPoints.push_back(std::make_pair(upperLegConfig.mtPt1, upperLegConfig.mtDir1));
	upperLegConfig.mountingPoints.push_back(std::make_pair(upperLegConfig.mtPt2, upperLegConfig.mtDir2));
	ci::gl::BatchRef mainBatchUpperLeg = ci::gl::Batch::create(upperLegConfig.upperLegShape, mGlslShadow);
	ci::gl::BatchRef shadowedBatchUpperLeg = ci::gl::Batch::create(upperLegConfig.upperLegShape, ci::gl::getStockShader(ci::gl::ShaderDef()));
	FLU.setup(false, upperLegConfig.mass, "FLU", mainBatchUpperLeg, shadowedBatchUpperLeg, upperLegConfig.size, upperLegConfig.mountingPoints, upperLegConfig.thisMountIndex, upperLegConfig.parentMountIndex);
	FRU.setup(false, upperLegConfig.mass, "FRU", mainBatchUpperLeg, shadowedBatchUpperLeg, upperLegConfig.size, upperLegConfig.mountingPoints, upperLegConfig.thisMountIndex, upperLegConfig.parentMountIndex);
	BLU.setup(false, upperLegConfig.mass, "BLU", mainBatchUpperLeg, shadowedBatchUpperLeg, upperLegConfig.size, upperLegConfig.mountingPoints, upperLegConfig.thisMountIndex, upperLegConfig.parentMountIndex);
	BRU.setup(false, upperLegConfig.mass, "BRU", mainBatchUpperLeg, shadowedBatchUpperLeg, upperLegConfig.size, upperLegConfig.mountingPoints, upperLegConfig.thisMountIndex, upperLegConfig.parentMountIndex);

	// front left leg lower
	lowerLegConfig.mountingPoints.push_back(std::make_pair(lowerLegConfig.mtPt1, lowerLegConfig.mtDir1));
	lowerLegConfig.mountingPoints.push_back(std::make_pair(lowerLegConfig.mtPt2, lowerLegConfig.mtDir2));
	ci::gl::BatchRef mainBatchLowerLeg = ci::gl::Batch::create(lowerLegConfig.lowerLegShape, mGlslShadow);
	ci::gl::BatchRef shadowedBatchLowerLeg = ci::gl::Batch::create(lowerLegConfig.lowerLegShape, ci::gl::getStockShader(ci::gl::ShaderDef()));
	FLL.setup(false, lowerLegConfig.mass, "FLL", mainBatchLowerLeg, shadowedBatchLowerLeg, lowerLegConfig.size, lowerLegConfig.mountingPoints, lowerLegConfig.thisMountIndex, lowerLegConfig.parentMountIndex);
	FRL.setup(false, lowerLegConfig.mass, "FRL", mainBatchLowerLeg, shadowedBatchLowerLeg, lowerLegConfig.size, lowerLegConfig.mountingPoints, lowerLegConfig.thisMountIndex, lowerLegConfig.parentMountIndex);
	BLL.setup(false, lowerLegConfig.mass, "BLL", mainBatchLowerLeg, shadowedBatchLowerLeg, lowerLegConfig.size, lowerLegConfig.mountingPoints, lowerLegConfig.thisMountIndex, lowerLegConfig.parentMountIndex);
	BRL.setup(false, lowerLegConfig.mass, "BRL", mainBatchLowerLeg, shadowedBatchLowerLeg, lowerLegConfig.size, lowerLegConfig.mountingPoints, lowerLegConfig.thisMountIndex, lowerLegConfig.parentMountIndex);

	root.addChild(FLS);
	FLS.addChild(FLU);
	FLU.addChild(FLL);

	root.addChild(FRS);
	FRS.addChild(FRU);
	FRU.addChild(FRL);

	root.addChild(BLS);
	BLS.addChild(BLU);
	BLU.addChild(BLL);

	root.addChild(BRS);
	BRS.addChild(BRU);
	BRU.addChild(BRL);
}


// void Root::setup(float _mass, std::string _name, ci::gl::BatchRef _mainBatch, ci::gl::BatchRef _shadowedBatch, ci::vec3 _pos, ci::vec3 _rot, ci::vec3 _size, std::vector<std::pair<ci::vec3, ci::vec3>> _mountingPoints)
// {
// 	visible = true;
// 	mass = _mass;
// 	name = _name;
// 	mainBatch = _mainBatch;
// 	shadowedBatch = _shadowedBatch;
// 	pos = _pos;
// 	rot = _rot;
// 	size = _size;
// 	mountingPoints = _mountingPoints;
// }
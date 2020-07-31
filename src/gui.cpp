#include "gui.h"

#include "cinder/app/App.h"


Gui::Gui()
{
	ImGui::Initialize(); 
}

void Gui::updateCamera(Cam &camera)
{
	float x = camera.cameraDistance * sinf(camera.cameraTheta) * cosf(camera.cameraPhi);
	float z = camera.cameraDistance * sinf(camera.cameraTheta) * sinf(camera.cameraPhi);
	float y = camera.cameraDistance * cosf(camera.cameraTheta);

	camera.mCam.lookAt(glm::vec3(x, y+camera.yOff, z), glm::vec3(0, camera.yOff,0));
	camera.mCam.setPerspective(30, ci::app::getWindowAspectRatio(), 100, 4000);
}

void Gui::updateCameraGUI(Cam &camera)
{
	ImGui::SetNextWindowCollapsed( false, ImGuiCond_FirstUseEver );
	ImGui::Begin( "Camera" );
	if (ImGui::Button("Reset Camera", ImVec2(100,30))) { camera.setCam(); }
	// ImGui::MenuItem("View", nullptr, true);
	// ImGui::DragFloat("Camera Theta", &camera.cameraTheta, 0.01, 0.001, 1.501);
	// ImGui::DragFloat("Camera Phi", &camera.cameraPhi, 0.01, -1000, 1000);
	// ImGui::DragFloat("Camera distance", &camera.cameraDistance, 2, 200, 2000);
	// ImGui::DragFloat("yOff", &camera.yOff, 1, -200, 200);
	ImGui::End();
}

void Gui::updateScene(Scene &scene, Robot &bot)
{
	ImGui::SetNextWindowCollapsed( false, ImGuiCond_FirstUseEver );
	ImGui::Begin( "Scene" );
	if (ImGui::Button("Toggle Floor", ImVec2(200,30))) { scene.showFloor = !scene.showFloor; }
	if (ImGui::Button("Toggle Mounting Point Lines", ImVec2(200,30))) { bot.showMtPtLines = !bot.showMtPtLines; }
	if (ImGui::Button("Toggle Mounting Point Axes", ImVec2(200,30))) { bot.showMtPtAxes = !bot.showMtPtAxes; }
	if (ImGui::Button("Toggle Joint Axes", ImVec2(200,30))) { bot.showLinkAxes = !bot.showLinkAxes; }
	if (ImGui::Button("Toggle Motor Rotation Vis", ImVec2(200,30))) { bot.showFullRotation = !bot.showFullRotation; }
	if (ImGui::Button("Toggle Motor Torque Vis", ImVec2(200,30))) { bot.showMotorTorques = !bot.showMotorTorques; }
	
	ImGui::MenuItem("Show links", nullptr, true);
	if (ImGui::Button("Toggle body", ImVec2(200,30))) { bot.body->visible = !bot.body->visible; }

	if (ImGui::Button("Toggle FLS", ImVec2(200,30))) { bot.FLS->visible = !bot.FLS->visible; }
	if (ImGui::Button("Toggle FRS", ImVec2(200,30))) { bot.FRS->visible = !bot.FRS->visible; }
	if (ImGui::Button("Toggle BLS", ImVec2(200,30))) { bot.BLS->visible = !bot.BLS->visible; }
	if (ImGui::Button("Toggle BRS", ImVec2(200,30))) { bot.BRS->visible = !bot.BRS->visible; }

	if (ImGui::Button("Toggle FLU", ImVec2(200,30))) { bot.FLU->visible = !bot.FLU->visible; }
	if (ImGui::Button("Toggle FRU", ImVec2(200,30))) { bot.FRU->visible = !bot.FRU->visible; }
	if (ImGui::Button("Toggle BLU", ImVec2(200,30))) { bot.BLU->visible = !bot.BLU->visible; }
	if (ImGui::Button("Toggle BRU", ImVec2(200,30))) { bot.BRU->visible = !bot.BRU->visible; }

	if (ImGui::Button("Toggle FLL", ImVec2(200,30))) { bot.FLL->visible = !bot.FLL->visible; }
	if (ImGui::Button("Toggle FRL", ImVec2(200,30))) { bot.FRL->visible = !bot.FRL->visible; }
	if (ImGui::Button("Toggle BLL", ImVec2(200,30))) { bot.BLL->visible = !bot.BLL->visible; }
	if (ImGui::Button("Toggle BRL", ImVec2(200,30))) { bot.BRL->visible = !bot.BRL->visible; }
	ImGui::End();
}

void Gui::updateRobotControl(Robot &robot)
{

}

void Gui::updateRobotConfig(Robot &robot)
{
	ImGui::SetNextWindowCollapsed( false, ImGuiCond_FirstUseEver );
	ImGui::Begin( "Robot config" );
	ImGui::MenuItem("Body Position", nullptr, true);
	ImGui::DragFloat("jointPoseTransBODY x", &robot.body->jointPoseTrans.x, 1, -100, 200);
	ImGui::DragFloat("jointPoseTransBODY y", &robot.body->jointPoseTrans.y, 1, -100, 200);
	ImGui::DragFloat("jointPoseTransBODY z", &robot.body->jointPoseTrans.z, 1, -100, 200);
	ImGui::MenuItem("Body Rotation", nullptr, true);
	ImGui::DragFloat("jointPoseRotBODY x", &robot.body->jointPoseRot.x, 0.01, 0.001, 1.501);
	ImGui::DragFloat("jointPoseRotBODY y", &robot.body->jointPoseRot.y, 0.01, 0.001, 1.501);
	ImGui::DragFloat("jointPoseRotBODY z", &robot.body->jointPoseRot.z, 0.01, 0.001, 1.501);
	ImGui::MenuItem("Body Joint Rotations", nullptr, true);
	ImGui::DragFloat("FLS jointAngle", &robot.FLS->jointAngle, 0.01, -1.501, 1.501*2);
	ImGui::DragFloat("FRS jointAngle", &robot.FRS->jointAngle, 0.01, -1.501, 1.501*2);
	ImGui::DragFloat("BLS jointAngle", &robot.BLS->jointAngle, 0.01, -1.501, 1.501*2);
	ImGui::DragFloat("BRS jointAngle", &robot.BRS->jointAngle, 0.01, -1.501, 1.501*2);
	ImGui::Separator();
	// ImGui::ColorPickerOptionsPopup();
	// ImGui::PlotLines();
	ImGui::MenuItem("Upper Leg Rotations", nullptr, true);
	ImGui::DragFloat("FLU jointAngle", &robot.FLU->jointAngle, 0.01, -3.1415, 3.1415);
	ImGui::DragFloat("FRU jointAngle", &robot.FRU->jointAngle, 0.01, -3.1415, 3.1415);
	ImGui::DragFloat("BLU jointAngle", &robot.BLU->jointAngle, 0.01, -3.1415, 3.1415);
	ImGui::DragFloat("BRU jointAngle", &robot.BRU->jointAngle, 0.01, -3.1415, 3.1415);
	ImGui::Separator();
	ImGui::MenuItem("Lower Leg Rotations", nullptr, true);
	ImGui::DragFloat("FLL jointAngle", &robot.FLL->jointAngle, 0.01, -3.1415, 3.1415);
	ImGui::DragFloat("FRL jointAngle", &robot.FRL->jointAngle, 0.01, -3.1415, 3.1415);
	ImGui::DragFloat("BLL jointAngle", &robot.BLL->jointAngle, 0.01, -3.1415, 3.1415);
	ImGui::DragFloat("BRL jointAngle", &robot.BRL->jointAngle, 0.01, -3.1415, 3.1415);
	ImGui::Separator();
	ImGui::Separator();
	ImGui::Separator();
	ImGui::Separator();
	ImGui::MenuItem("FRL TESTS", nullptr, true);
	ImGui::DragFloat("FRL x", &robot.FRL->jointPoseRot.x, 0.01, -3.1415, 3.1415);
	ImGui::DragFloat("FRL y", &robot.FRL->jointPoseRot.y, 0.01, -3.1415, 3.1415);
	ImGui::DragFloat("FRL z", &robot.FRL->jointPoseRot.z, 0.01, -3.1415, 3.1415);
	ImGui::End();
}

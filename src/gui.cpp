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
	if (ImGui::Button("Toggle Joint Axes", ImVec2(200,30))) { bot.showJointAxes = !bot.showJointAxes; }
	if (ImGui::Button("Toggle Motor Rotation Vis", ImVec2(200,30))) { bot.showFullRotation = !bot.showFullRotation; }
	if (ImGui::Button("Toggle Motor Torque Vis", ImVec2(200,30))) { bot.showMotorTorques = !bot.showMotorTorques; }
	
	ImGui::MenuItem("Show links", nullptr, true);
	if (ImGui::Button("Toggle body", ImVec2(200,30))) { bot.body.visible = !bot.body.visible; }

	if (ImGui::Button("Toggle FLS", ImVec2(200,30))) { bot.FLS.visible = !bot.FLS.visible; }
	if (ImGui::Button("Toggle FRS", ImVec2(200,30))) { bot.FRS.visible = !bot.FRS.visible; }
	if (ImGui::Button("Toggle BRS", ImVec2(200,30))) { bot.BLS.visible = !bot.BLS.visible; }
	if (ImGui::Button("Toggle BRS", ImVec2(200,30))) { bot.BRS.visible = !bot.BRS.visible; }

	if (ImGui::Button("Toggle FLU", ImVec2(200,30))) { bot.FLU.visible = !bot.FLU.visible; }
	if (ImGui::Button("Toggle FRU", ImVec2(200,30))) { bot.FRU.visible = !bot.FRU.visible; }
	if (ImGui::Button("Toggle BLU", ImVec2(200,30))) { bot.BLU.visible = !bot.BLU.visible; }
	if (ImGui::Button("Toggle BRU", ImVec2(200,30))) { bot.BRU.visible = !bot.BRU.visible; }

	if (ImGui::Button("Toggle FLL", ImVec2(200,30))) { bot.FLL.visible = !bot.FLL.visible; }
	if (ImGui::Button("Toggle FRL", ImVec2(200,30))) { bot.FRL.visible = !bot.FRL.visible; }
	if (ImGui::Button("Toggle BLL", ImVec2(200,30))) { bot.BLL.visible = !bot.BLL.visible; }
	if (ImGui::Button("Toggle BRL", ImVec2(200,30))) { bot.BRL.visible = !bot.BRL.visible; }
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
	ImGui::DragFloat("centerPos x", &robot.body.centerPos.x, 1, -100, 200);
	ImGui::DragFloat("centerPos y", &robot.body.centerPos.y, 1, -100, 200);
	ImGui::DragFloat("centerPos z", &robot.body.centerPos.z, 1, -100, 200);
	ImGui::MenuItem("Body Rotation", nullptr, true);
	ImGui::DragFloat("centerRot x", &robot.body.centerRot.x, 0.01, 0.001, 1.501);
	ImGui::DragFloat("centerRot y", &robot.body.centerRot.y, 0.01, 0.001, 1.501);
	ImGui::DragFloat("centerRot z", &robot.body.centerRot.z, 0.01, 0.001, 1.501);
	ImGui::MenuItem("Body Joint rotations", nullptr, true);
	ImGui::DragFloat("FLS rotation", &robot.FLS.jointAngle, 0.01, -1.501, 1.501);
	ImGui::DragFloat("FRS rotation", &robot.FRS.jointAngle, 0.01, -1.501, 1.501);
	ImGui::DragFloat("BLS rotation", &robot.BLS.jointAngle, 0.01, -1.501, 1.501);
	ImGui::DragFloat("BRS rotation", &robot.BRS.jointAngle, 0.01, -1.501, 1.501);
	ImGui::Spacing();
	// ImGui::ColorPickerOptionsPopup();
	// ImGui::PlotLines();
	ImGui::MenuItem("FLS Position", nullptr, true);
	ImGui::DragFloat("centerPosFLS x", &robot.FLS.centerPos.x, 1, -100, 200);
	ImGui::DragFloat("centerPosFLS y", &robot.FLS.centerPos.y, 1, -100, 200);
	ImGui::DragFloat("centerPosFLS z", &robot.FLS.centerPos.z, 1, -100, 200);
	ImGui::MenuItem("FLS Rotation", nullptr, true);
	ImGui::DragFloat("centerRotFLS x", &robot.FLS.centerRot.x, 0.01, 0.001, 1.501);
	ImGui::DragFloat("centerRotFLS y", &robot.FLS.centerRot.y, 0.01, 0.001, 1.501);
	ImGui::DragFloat("centerRotFLS z", &robot.FLS.centerRot.z, 0.01, 0.001, 1.501);
	// ImGui::MenuItem("Shins", nullptr, true);
	// ImGui::DragFloat("Length Shins", &cameraTheta31, 0.01, 0.001, 1.501);
	// ImGui::DragFloat("Width Shins", &cameraTheta32, 0.01, 0.001, 1.501);
	// ImGui::DragFloat("Height Shins", &cameraTheta33, 0.01, 0.001, 1.501);
	ImGui::End();
}

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
	ImGui::Begin( "Params" );
	ImGui::MenuItem("View", nullptr, true);
	ImGui::DragFloat("Camera Theta", &camera.cameraTheta, 0.01, 0.001, 1.501);
	ImGui::DragFloat("Camera Phi", &camera.cameraPhi, 0.01, -1000, 1000);
	ImGui::DragFloat("Camera distance", &camera.cameraDistance, 2, 500, 2000);
	ImGui::DragFloat("yOff", &camera.yOff, 1, -200, 200);
	ImGui::End();

	ImGui::SetNextWindowCollapsed( false, ImGuiCond_FirstUseEver );
	ImGui::Begin( "Robot config" );
	// ImGui::MenuItem("Body", nullptr, true);
	// ImGui::DragFloat("Length Body", &cameraTheta11, 0.01, 0.001, 1.501);
	// ImGui::DragFloat("Width Body", &cameraTheta12, 0.01, 0.001, 1.501);
	// ImGui::DragFloat("Height Body", &cameraTheta13, 0.01, 0.001, 1.501);
	// ImGui::MenuItem("Thighs", nullptr, true);
	// ImGui::DragFloat("Length Thighs", &cameraTheta21, 0.01, 0.001, 1.501);
	// ImGui::DragFloat("Width Thighs", &cameraTheta22, 0.01, 0.001, 1.501);
	// ImGui::DragFloat("Height Thighs", &cameraTheta23, 0.01, 0.001, 1.501);
	// ImGui::MenuItem("Shins", nullptr, true);
	// ImGui::DragFloat("Length Shins", &cameraTheta31, 0.01, 0.001, 1.501);
	// ImGui::DragFloat("Width Shins", &cameraTheta32, 0.01, 0.001, 1.501);
	// ImGui::DragFloat("Height Shins", &cameraTheta33, 0.01, 0.001, 1.501);
	ImGui::End();
}

void Gui::updateScene(Scene &scene)
{
	ImGui::Begin( "Params" );
	ImGui::MenuItem("Scene", nullptr, true);
	if (ImGui::Button("Toggle Floor", ImVec2(100,30))) 
	{
		scene.showFloor = !scene.showFloor;
	}
	ImGui::End();
}

void Gui::updateRobotControl(Robot &robot)
{

}

void Gui::updateRobotConfig(Robot &robot)
{
	
}
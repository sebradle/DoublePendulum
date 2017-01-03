#include "GUI.h"
#include <sstream>
#include <string>
#include <iostream>

GUI::GUI() : numPendulums(0), selectedPendulum(0)
{
}


GUI::~GUI()
{
}


void GUI::init(Engine::Window* window) {
	mWindow = window;
	bool show_another_window = false;
	selectedPendulum = 0;
	numPendulums = 0;
	amPaused = Paused::PAUSE;
}

void GUI::update() {

}

void GUI::render() {
	ImGui_ImplSdlGL3_NewFrame(mWindow->getWindow());





	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (!no_border)   window_flags |= ImGuiWindowFlags_ShowBorders;
	if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
	if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
	if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;

	{
		ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Double Pendulum Demo", &show_another_window, window_flags);
		// Pendulum Menu
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Pendulums"))
			{
				for (int i = 0; i < numPendulums; i++) {
					ShowPendulumMenu(i + 1);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		std::string pend = "Pendulum #";
		std::stringstream str;
		str << selectedPendulum + 1;
		pend += str.str();
		ImGui::Text(pend.c_str());
		ImGui::ColorEdit3("Floor", (float*)&mPendulums[selectedPendulum].pFloorColor);
		ImGui::ColorEdit3("BG", (float*)&mPendulums[selectedPendulum].pBGColor);
		ImGui::DragFloat("Mass 1", &mPendulums[selectedPendulum].pMass1, 0.1, 0.2f, 100.0f, "%.3f");
		ImGui::DragFloat("Length 1", &mPendulums[selectedPendulum].pLength1, 0.1, 0.45f, 15.0f, "%.3f");
		ImGui::DragFloat("Angle 1", &mPendulums[selectedPendulum].pAngle1, 0.5, 0.0f, 360.0f, "%.3f deg");
		ImGui::ColorEdit3("Top", (float*)&mPendulums[selectedPendulum].pTopColor);
		ImGui::DragFloat("Mass 2", &mPendulums[selectedPendulum].pMass2, 0.1, 0.2f, 100.0f, "%.3f");
		ImGui::DragFloat("Length 2", &mPendulums[selectedPendulum].pLength2, 0.1, 0.45f, 15.0f, "%.3f");
		ImGui::DragFloat("Angle 2", &mPendulums[selectedPendulum].pAngle2, 0.5, 0.0f, 360.0f, "%.3f deg");
		ImGui::ColorEdit3("Bot", (float*)&mPendulums[selectedPendulum].pBotColor);
		if (ImGui::Button("Pause")) amPaused = Paused::PAUSE; ImGui::SameLine();
		if (ImGui::Button("Start")) amPaused = Paused::START; ImGui::SameLine();
		if (ImGui::Button("Reset")) amPaused = Paused::RESET; 
		if (ImGui::Button("Add Pendulum")) addPendulum(); ImGui::SameLine();
		if (ImGui::Button("Remove Pendulum")) removePendulum();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
	ImGui::Render();
}

void GUI::ShowPendulumMenu(int pendulumNum)
{
	std::string select = "Select ";
	std::stringstream str;
	str << pendulumNum;
	select += str.str();

	if (ImGui::Button(select.c_str())) selectedPendulum = pendulumNum - 1;
}


void GUI::addPendulum() {
	if (numPendulums < MAX_PENDULUMS) {
		PendulumData data;

		ImVec4 bg(DEFAULT_BACKGROUND_COLOR.x, DEFAULT_BACKGROUND_COLOR.y, DEFAULT_BACKGROUND_COLOR.z, DEFAULT_BACKGROUND_COLOR.z);
		ImVec4 fc(DEFAULT_FLOOR_COLOR.x, DEFAULT_FLOOR_COLOR.y, DEFAULT_FLOOR_COLOR.z, DEFAULT_FLOOR_COLOR.z);
		ImVec4 red(DEFAULT_BOT_COLOR.x, DEFAULT_BOT_COLOR.y, DEFAULT_BOT_COLOR.z, DEFAULT_BOT_COLOR.z);
		ImVec4 blue(DEFAULT_TOP_COLOR.x, DEFAULT_TOP_COLOR.y, DEFAULT_TOP_COLOR.z, DEFAULT_TOP_COLOR.z);

		data.pBGColor = bg;
		data.pFloorColor = fc;
		data.pTopColor = blue;
		data.pBotColor = red;
		data.pMass1 = DEFAULT_MASS;
		data.pMass2 = DEFAULT_MASS;
		data.pLength1 = DEFAULT_LENGTH;
		data.pLength2 = DEFAULT_LENGTH;
		data.pAngle1 = 90.0f;
		data.pAngle2 = 180.0f;
		mPendulums.push_back(data);
		numPendulums++;
	}
}

void GUI::removePendulum() {
	if (numPendulums > 1) {
		mPendulums.pop_back();
		numPendulums--;
	}
}
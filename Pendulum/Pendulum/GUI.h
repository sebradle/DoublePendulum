#pragma once
#include <Engine/imgui/imgui.h>
#include <Engine/imgui_impl_sdl_gl3.h>
#include <Engine/Window.h>
#include <vector>
#include "Pendulum.h"
#include "DoublePendulum.h"


class GUI
{
public:
	GUI();
	~GUI();

	void init(Engine::Window* window);
	void update();
	void render();
	void addPendulum();
	void removePendulum();

	// Setters
	void setAmPaused(Paused pause) { amPaused = pause; }

	// Getters
	Paused getAmPaused() { return amPaused; }
	PendulumData getSelectedData() { return mPendulums[selectedPendulum]; }
	int getSelected() { return selectedPendulum; }
	int getNumPendulums() { return numPendulums; }

private:
	Engine::Window* mWindow;

	bool show_another_window;

	std::vector<PendulumData> mPendulums;
	void ShowPendulumMenu(int pendulumNum);

	int numPendulums;
	int selectedPendulum;
	Paused amPaused;

	static const bool no_titlebar = false;
	static const bool no_border = true;
	static const bool no_resize = true;
	static const bool no_move = true;
	static const bool no_scrollbar = true;
	static const bool no_collapse = true;
	static const bool no_menu = false;
};


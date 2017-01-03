#pragma once

#include <Engine/imgui/imgui.h>
#include <glm/glm.hpp>

struct PendulumData {
	ImVec4 pBGColor;
	ImVec4 pFloorColor;
	ImVec4 pTopColor;
	ImVec4 pBotColor;

	float pMass1;
	float pLength1;
	float pAngle1;
	float pMass2;
	float pLength2;
	float pAngle2;
};

enum class Paused { PAUSE, START, RESET, UPDATE };

enum class State { PLAY, EXIT };

const int MAX_PENDULUMS = 8;

const glm::vec4 DEFAULT_FLOOR_COLOR(0.8f, 0.8f, 0.8f, 1.0f);
const glm::vec4 DEFAULT_BACKGROUND_COLOR(0.58f, 0.65f, 0.76f, 1.0f);
const glm::vec4 DEFAULT_BOT_COLOR(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 DEFAULT_TOP_COLOR(0.0f, 0.0f, 1.0f, 1.0f);
const glm::vec3 FLOOR_DEPTH = glm::vec3(0.0f, -61.0f, 0.0f);

const float DEFAULT_LENGTH = 1.0f;
const float DEFAULT_MASS = 1.0f;
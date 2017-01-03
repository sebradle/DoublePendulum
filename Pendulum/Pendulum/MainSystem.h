#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include <Engine/Engine.h>
#include <Engine/GLSLProgram.h>
#include <Engine/Texture.h>
#include <Engine/Window.h>
#include <Engine/Camera.h>
#include <Engine/ModelBatch.h>
#include <Engine/ResourceManager.h>
#include <Engine/InputManager.h>

#include <vector>
#include "DoublePendulum.h"
#include "Scene.h"
#include "GUI.h"
#include "Pendulum.h"


class MainSystem
{
public:
	MainSystem();
	~MainSystem();

	void run();

private:
	void initSystems();
	void initShaders();
	void mainLoop();
	void updatePendulums();
	void processInput();
	void draw();
	void BuildMatrices();
	void SetMaterial(glm::vec4 ka, glm::vec4 kd, glm::vec4 ks, float s);
	void SetLight(glm::vec4 lpos, glm::vec4 la, glm::vec4 ld, glm::vec4 ls);
	void fps();

	Engine::Window mWindow;
	Engine::Camera mCamera;

	int mScreenWidth;
	int mScreenHeight;
	State mCurrentState;

	Engine::GLSLProgram mColorProgram;
	Engine::ModelBatch mBatch;
	Engine::InputManager mInputManager;


	float prevAngle1;
	float prevAngle2;
	float mMaxFPS;
	float mFPS;
	float mFrameTime;
	float mTime;

	DoublePendulum pendulums[MAX_PENDULUMS];
	Scene myScene;
	GUI myGUI;
};


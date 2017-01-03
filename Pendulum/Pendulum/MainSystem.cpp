#include "MainSystem.h"

#include <Engine/Errors.h>
#include <Engine/imgui/imgui.h>
#include <Engine/imgui_impl_sdl_gl3.h>
#include <iostream>

MainSystem::MainSystem() :
	mScreenWidth(1024),
	mScreenHeight(768),
	mTime(0.0f),
	mCurrentState(State::PLAY),
	mMaxFPS(60.0f)
{
}


MainSystem::~MainSystem()
{
}

void MainSystem::run() {
	initSystems();
	mainLoop();
}

void MainSystem::initSystems() {
	Engine::init();
	mWindow.create("Pendulum", mScreenWidth, mScreenHeight, Engine::FULLSCREEN);
	initShaders();
	mBatch.init();

	prevAngle1 = M_PI / 2.0f;;
	prevAngle2 = M_PI;
	// Initialize Pendulums
	float z = 0.0f;
	for (int i = 0; i < MAX_PENDULUMS; i++) {
		DoublePendulum pendulum;
		pendulum.init(DEFAULT_LENGTH, DEFAULT_MASS, M_PI / 2.0f, DEFAULT_LENGTH, DEFAULT_MASS, M_PI, glm::vec3(0.0f, 0.0f, z));
		z = z - 3.0f;
		pendulums[i] = pendulum;
	}

	// Initialize Scene
	myScene.init(DEFAULT_FLOOR_COLOR, DEFAULT_BACKGROUND_COLOR, FLOOR_DEPTH);

	// Initialize GUI
	myGUI.init(&mWindow);
	myGUI.addPendulum();
}

void MainSystem::initShaders() {
	mColorProgram.compileShaders("Shaders/vshader.glsl", "Shaders/fshader.glsl");
	mColorProgram.addAttribute("vertexPosition");
	mColorProgram.addAttribute("vertexUV");
	mColorProgram.addAttribute("vertexNormal");
	mColorProgram.linkShaders();
}


void MainSystem::mainLoop() {
	while(mCurrentState != State::EXIT) {
		float start = SDL_GetTicks();

		processInput();
		mTime += 0.01;

		draw();
		fps();

		updatePendulums();
		
		static int frameCount = 0;
		frameCount++;
		//if (frameCount % 10 == 0) std::cout << mFPS << std::endl;

		float frameTicks = SDL_GetTicks() - start;
		if (1000.0f / mMaxFPS > frameTicks) {
			SDL_Delay(1000.0f / mMaxFPS - frameTicks);
		}
	}
}

void MainSystem::updatePendulums() {
	PendulumData data = myGUI.getSelectedData();

	// Set Colors of Scene
	glm::vec4 tc(data.pTopColor.x, data.pTopColor.y, data.pTopColor.z, data.pTopColor.w);
	glm::vec4 bc(data.pBotColor.x, data.pBotColor.y, data.pBotColor.z, data.pBotColor.w);
	glm::vec4 bg(data.pBGColor.x, data.pBGColor.y, data.pBGColor.z, data.pBGColor.w);
	glm::vec4 fl(data.pFloorColor.x, data.pFloorColor.y, data.pFloorColor.z, data.pFloorColor.w);
	myScene.set(bg, fl);
	pendulums[myGUI.getSelected()].setKAs(tc, bc);

	if (myGUI.getAmPaused() == Paused::PAUSE) {
		if (data.pAngle1 != prevAngle1 || data.pAngle2 != prevAngle2) {
			myGUI.setAmPaused(Paused::UPDATE);
			prevAngle1 = data.pAngle1;
			prevAngle2 = data.pAngle2;
		}
	}

	pendulums[myGUI.getSelected()].setMasses(data.pMass1, data.pMass2);
	pendulums[myGUI.getSelected()].setLengths(data.pLength1, data.pLength2);
	if (myGUI.getAmPaused() == Paused::UPDATE ) {
		pendulums[myGUI.getSelected()].setAngles(data.pAngle1 * (M_PI / 180.0f), data.pAngle2 * (M_PI / 180.0f));
	}
	pendulums[myGUI.getSelected()].calcPosition();


	if (myGUI.getAmPaused() == Paused::START) {
		for (int i = 0; i < myGUI.getNumPendulums(); i++) {
			pendulums[i].update();
		}
	}

	if (myGUI.getAmPaused() == Paused::RESET) {
		float z = 0.0f;
		for (int i = 0; i < myGUI.getNumPendulums(); i++) {
			pendulums[i].init(DEFAULT_LENGTH, DEFAULT_MASS, M_PI / 2.0f, DEFAULT_LENGTH, DEFAULT_MASS, M_PI, glm::vec3(0.0f, 0.0f, z));
			z = z - 3.0f;
		}
		myGUI.setAmPaused(Paused::UPDATE);
	}
}

void MainSystem::processInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		ImGui_ImplSdlGL3_ProcessEvent(&evnt);
		switch (evnt.type) {
		case SDL_QUIT:
			mCurrentState = State::EXIT;
			break;
		case SDL_MOUSEMOTION:
			mInputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			mInputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			mInputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			mInputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			mInputManager.releaseKey(evnt.button.button);
			break;
		}
	}

	if (mInputManager.isKeyPressed(SDLK_ESCAPE)) {
		mCurrentState = State::EXIT;
	}
	if (mInputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		mCamera.update(mInputManager.getMouseCoords());
	}
	if (mInputManager.isKeyPressed(SDLK_w)) {
		mCamera.moveFoward();
	}
	if (mInputManager.isKeyPressed(SDLK_a)) {
		mCamera.strafeLeft();
	}
	if (mInputManager.isKeyPressed(SDLK_s)) {
		mCamera.moveBackward();
	}
	if (mInputManager.isKeyPressed(SDLK_d)) {
		mCamera.strafeRight();
	}
	if (mInputManager.isKeyPressed(SDLK_r)) {
		mCamera.moveUp();
	}
	if (mInputManager.isKeyPressed(SDLK_f)) {
		mCamera.moveDown();
	}
	//if (mInputManager.isKeyPressed(SDLK_1)) {
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//}
	//if (mInputManager.isKeyPressed(SDLK_2)) {
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//}
	//if (mInputManager.isKeyPressed(SDLK_l)) {
	//	pendulums[0].setLengths(pendulums[0].getLength1() + 0.1f, pendulums[0].getLength2());
	//}
	//if (mInputManager.isKeyPressed(SDLK_k)) {
	//	pendulums[0].setLengths(pendulums[0].getLength1(), pendulums[0].getLength2() + 0.1f);
	//}
}




bool show_test_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImColor(255, 0, 0);

void MainSystem::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mColorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	
	
	BuildMatrices();

	GLint modelID = mColorProgram.getUniformLocation("model");
	static Engine::GLTexture red = Engine::ResourceManager::getTexture("Textures/earth.png");
	float z = 0.0f;
	for (int i = 0; i < myGUI.getNumPendulums(); i++) {
		SetLight(glm::vec4(0.0, 15.0, z, 1.0), glm::vec4(0.7, 0.7, 0.7, 1.0), glm::vec4(0.9, 0.9, 0.9, 1.0), glm::vec4(0.5, 0.5, 0.5, 1.0));
		z = z - 3.0f;
		pendulums[i].draw(mBatch, red.id, mColorProgram);
	}

	myScene.draw(mBatch, red.id, mColorProgram);
	myGUI.render();

	glBindTexture(GL_TEXTURE_2D, 0);
	mColorProgram.unuse();

	mWindow.swapBuffer();
}

void MainSystem::BuildMatrices()
{
	// Set texture locations
	GLint texLocation = mColorProgram.getUniformLocation("mySampler");
	glUniform1i(texLocation, 0);

	// Build Proj and View matrices
	glm::mat4 proj = mCamera.getProjMatrix(mScreenWidth, mScreenHeight);
	glm::mat4 view = mCamera.getViewMatrix();

	GLint projID = mColorProgram.getUniformLocation("proj");
	glUniformMatrix4fv(projID, 1, GL_FALSE, &proj[0][0]);

	GLint viewID = mColorProgram.getUniformLocation("view");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);

	// Not using textures, light always on
	glUniform1i(mColorProgram.getUniformLocation("light_out"), false);
	glUniform1i(mColorProgram.getUniformLocation("texture_on"), false);
}

void MainSystem::SetMaterial(glm::vec4 ka, glm::vec4 kd, glm::vec4 ks, float s)
{
	glUniform4fv(mColorProgram.getUniformLocation("ka"), 1, &ka[0]);
	glUniform4fv(mColorProgram.getUniformLocation("kd"), 1, &kd[0]);
	glUniform4fv(mColorProgram.getUniformLocation("ks"), 1, &ks[0]);
	glUniform1f(mColorProgram.getUniformLocation("Shininess"), s);
}

void MainSystem::SetLight(glm::vec4 lpos, glm::vec4 la, glm::vec4 ld, glm::vec4 ls)
{
	glUniform4fv(mColorProgram.getUniformLocation("LightPos"), 1, &lpos[0]);
	glUniform4fv(mColorProgram.getUniformLocation("Ambient"), 1, &la[0]);
	glUniform4fv(mColorProgram.getUniformLocation("Diffuse"), 1, &ld[0]);
	glUniform4fv(mColorProgram.getUniformLocation("Specular"), 1, &ls[0]);
}


void MainSystem::fps() {
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currTicks;
	currTicks = SDL_GetTicks();

	mFrameTime = currTicks - prevTicks;
	frameTimes[currFrame % NUM_SAMPLES] = mFrameTime;
	prevTicks = currTicks;

	int count;
	currFrame++;

	if (currFrame < NUM_SAMPLES) {
		count = currFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	float frameAverage = 0;

	for (int i = 0; i < count; i++) {
		frameAverage += frameTimes[i];
	}

	frameAverage /= count;

	if (frameAverage > 0) {
		mFPS = 1000.0f / frameAverage;
	}
	else {
		mFPS = 60.0f;
	}
}
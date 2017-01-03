#include "Window.h"
#include "Errors.h"
#include "imgui\imgui.h"
#include "imgui_impl_sdl_gl3.h"

namespace Engine {
	Window::Window()
	{
	}


	Window::~Window()
	{
		ImGui_ImplSdlGL3_Shutdown();
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

		Uint32 flag = SDL_WINDOW_OPENGL | currentFlags;

		mWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flag);
		if (mWindow == nullptr) {
			fatalError("Window not created");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(mWindow);
		if (glContext == nullptr) {
			fatalError("SDL_GL context could not be created");
		}
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew");
		}

		//
		ImGui_ImplSdlGL3_Init(mWindow);
		//

		std::printf("*** OpenGL Version: %s ***", glGetString(GL_VERSION));

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		SDL_GL_SetSwapInterval(1);

		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(mWindow);
	}
}
#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
namespace Engine {
	enum WindowFlags {
		NONE = 0,
		FULLSCREEN = SDL_WINDOW_FULLSCREEN_DESKTOP,
		INVISIBLE = SDL_WINDOW_HIDDEN,
		BORDERLESS = SDL_WINDOW_BORDERLESS,
		RESIZEABLE = SDL_WINDOW_RESIZABLE,
		MINIMIZED = SDL_WINDOW_MINIMIZED,
		MAXIMIZED = SDL_WINDOW_MAXIMIZED,
		INPUT_GRABBED = SDL_WINDOW_INPUT_GRABBED,
		INPUT_FOCUS = SDL_WINDOW_INPUT_FOCUS,
		MOUSE_FOCUS = SDL_WINDOW_MOUSE_FOCUS,
		MOUSE_CAPTURE = SDL_WINDOW_MOUSE_CAPTURE
	};

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
		//
		SDL_Window* getWindow() { return mWindow; }
		//
		void swapBuffer();

		int getScreenWidth() { mWidth; }
		int getScreenHeight() { mHeight; }

	private:
		SDL_Window* mWindow;
		int mWidth;
		int mHeight;
	};

}
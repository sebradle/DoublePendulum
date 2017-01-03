#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

namespace Engine {
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);

		bool isKeyPressed(unsigned int keyID);

		//getters
		glm::vec2 getMouseCoords() const { return mMouseCoords; }
	private:

		std::unordered_map<unsigned int, bool> mKeyMap;
		glm::vec2 mMouseCoords;
	};

}
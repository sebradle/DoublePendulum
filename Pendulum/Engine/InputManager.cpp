#include "InputManager.h"
namespace Engine {


	InputManager::InputManager() : mMouseCoords(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}


	void InputManager::pressKey(unsigned int keyID) {
		mKeyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID) {
		mKeyMap[keyID] = false;
	}

	void InputManager::setMouseCoords(float x, float y) {
		mMouseCoords.x = x;
		mMouseCoords.y = y;
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		auto it = mKeyMap.find(keyID);
		if (it != mKeyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}
}
#include "ResourceManager.h"
namespace Engine {
	TextureCache ResourceManager::mTextCache;

	GLTexture ResourceManager::getTexture(std::string texturePath) {
		return mTextCache.getTexture(texturePath);
	}
}
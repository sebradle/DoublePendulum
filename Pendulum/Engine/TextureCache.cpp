#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
namespace Engine {
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}


	GLTexture TextureCache::getTexture(std::string texturePath) {

		auto it = mTextureMap.find(texturePath);

		if (it == mTextureMap.end()) {
			GLTexture newText = ImageLoader::loadPNG(texturePath);

			mTextureMap.insert(make_pair(texturePath, newText));

			std::cout << "Loaded text" << std::endl;

			return newText;
		}
		std::cout << "Used cached text" << std::endl;
		return it->second;
	}
}
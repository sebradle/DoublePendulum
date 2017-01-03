#pragma once
#include <map>
#include "Texture.h"

namespace Engine {
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> mTextureMap;
	};
}

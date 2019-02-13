#pragma once
#include "TextureCache.h"
#include <string>
namespace GameEngine
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);
		//static GLuint _boundTexture;
	private:
		static TextureCache _textureCache;
	};

}
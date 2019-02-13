#pragma once
#include "texture.h"
#include <string>
namespace GameEngine
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};

}
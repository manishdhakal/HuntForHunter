#pragma once
#include "texture.h"
#include <string>
class ImageLoader
{
public:
	static GLTexture loadPNG(std::string filePath);
};
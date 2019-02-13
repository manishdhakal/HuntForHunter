#pragma once
#include<map>
#include "texture.h"
#include "ImageLoader.h"
class TextureCache
{
public:
	TextureCache();
	~TextureCache();
	GLTexture getTexture(std::string texturePath);
private:
	std::map<std::string, GLTexture>  _textureMap;
};


#include "ImageLoader.h"
#define	STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include "IOManager.h"
#include <fstream>
#include <sstream>
namespace GameEngine
{
	GLTexture ImageLoader::loadPNG(std::string filePath)
	{
		GLTexture texture = {};
		int x, y, n;
		unsigned char* pixels = stbi_load(filePath.c_str(), &x, &y, &n, 4);


		glGenTextures(1, &(texture.id));
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		stbi_image_free(pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		texture.width = x;
		texture.height = y;
		return texture;
	}

}
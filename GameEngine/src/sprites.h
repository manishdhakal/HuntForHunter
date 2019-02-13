#pragma once
#include <glew.h>
#include "texture.h"
//#include"maingame.h"
#include <string>
namespace GameEngine
{
	class sprites
	{
	public:
		sprites();
		~sprites();
		void init(float x, float y, float width, float height, std::string texturePath);
		void draw();
	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID;
		GLTexture _texture;


	};

}
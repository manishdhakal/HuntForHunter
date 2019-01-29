#pragma once
#include <glew.h>
class sprites
{
public:
	sprites();
	~sprites();
	void init(float x,float y,float width,float height);
	void draw();
private:
	float _x;
	float _y;
	float _width;
	float _height;
	GLuint _vboID;
};


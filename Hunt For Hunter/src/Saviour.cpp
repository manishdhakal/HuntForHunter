#include "Saviour.h"
#include"SDL.h"


Saviour::Saviour()
{
}


Saviour::~Saviour()
{
}

void Saviour::init(int speed, glm::vec2 pos)
{
	_speed = speed;
	_position = pos;
	_color.r = 242;
	_color.g = 147;
	_color.b = 106;
	_color.a = 255;


}

void Saviour::update(GameEngine::keyHandler& keyHandler)
{
	if (keyHandler.iskeyPressed(SDLK_w))
	{
		_position.x -= _speed;
	}
	else if (keyHandler.iskeyPressed(SDLK_s))
	{
		_position.x += _speed;
	}
	if (keyHandler.iskeyPressed(SDLK_a))
	{
		_position.y -= _speed;
	}
	else if (keyHandler.iskeyPressed(SDLK_d))
	{
		_position.y += _speed;
	}
}

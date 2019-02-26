#include "Poachers.h"



Poachers::Poachers()
{
}


Poachers::~Poachers()
{
}

void Poachers::init(float speed, glm::vec2 pos)
{
	_speed = speed;
	_position = pos;
	_color.r = 255;
	_color.g = 255;
	_color.b = 255;
	_color.a = 255;
}

void Poachers::update(const std::vector<std::string>& levelData,
	std::vector<Animal*>& animals,
	std::vector <Poachers*>& poachers)
{

	CollideWithLevel(levelData);


}


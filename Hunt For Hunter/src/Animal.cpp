#include "Animal.h"
#include"ctime"
#include<random>

Animal::Animal()
{
}


Animal::~Animal()
{
}

void Animal::init(float speed, glm::vec2 pos)
{

	static std::mt19937 randomEngine(time(nullptr));
	
	static std::uniform_real_distribution<float> ranDir(-1.0f, 1.0f);

	_color.r = 255;
	_color.g = 255;
	_color.b = 255;
	_color.a = 255;

	_speed = speed;
	_position = pos;
	_direction = glm::vec2(ranDir(randomEngine), ranDir(randomEngine));

	if (_direction.length() == 0)
	{
		_direction = glm::vec2(1.0f, 0.0f);
	}

	_direction = glm::normalize(_direction);

}


void Animal::update(const std::vector<std::string>& levelData,
	std::vector<Animal*>& animals,
	std::vector <Poachers*>& poachers)
{

	_position += _direction * _speed;
	CollideWithLevel(levelData);
}


#define GLM_ENABLE_EXPERIMENTAL

#include "Animal.h"



#include"ctime"
#include<random>
#include<gtx/rotate_vector.hpp>


Animal::Animal()
{
	_frames = 0;
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
	static std::mt19937 randomEngine(time(nullptr));

	static std::uniform_real_distribution<float> randRotate(-40.0f, 40.0f);


	_position += _direction * _speed;

	if (_frames == 20)
	{

		_direction = glm::rotate(_direction, randRotate(randomEngine));
		_frames = 0;
	}
	else
	{
		_frames++;
	}

	if (CollideWithLevel(levelData))
	{
		_direction = glm::rotate(_direction, randRotate(randomEngine));

	}
}
#include "Poachers.h"
#include"Animal.h"


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
	_health = 50;
	_color.r = 255;
	_color.g = 255;
	_color.b = 255;
	_color.a = 255;
}

void Poachers::update(const std::vector<std::string>& levelData,
	std::vector<Animal*>& animals,
	std::vector <Poachers*>& poachers)
{
	Animal* closestAnimal = getNearestAnimal(animals);

	if (closestAnimal != nullptr)
	{
		glm::vec2 direction = glm::normalize(closestAnimal->getposition() - _position);

		_position += direction * _speed;

	}

	CollideWithLevel(levelData);


}

Animal* Poachers::getNearestAnimal(std::vector<Animal*>& animals)
{

	Animal* closestAnimal = nullptr;

	float smallestDistance = 99999999.0f;

	for (int i = 0; i < animals.size(); i++)
	{
		glm::vec2 distVec = animals[i]->getposition() - _position;

		float distance = glm::length(distVec);

		if (distance < smallestDistance)
		{
			smallestDistance = distance;
			closestAnimal = animals[i];

		}

	}

	return closestAnimal;
}



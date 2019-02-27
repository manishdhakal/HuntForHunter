#pragma once

#include<glm.hpp>
#include<vector>
class Animal;
class Poachers;

class Bullets
{
public:
	Bullets(glm::vec2 position,glm::vec2 direction,float damage , float speed);
	~Bullets();

	void update(std::vector<Animal*>& animals,
		std::vector <Poachers*>& poachers);

private:
	float _damage;
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
};


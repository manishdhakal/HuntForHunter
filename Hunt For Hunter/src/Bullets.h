#pragma once

#include<glm.hpp>
#include<vector>
#include<SpriteBatch.h>
class Animal;
class Poachers;

const int BULLET_RADIUS=5;

class Bullets
{
public:
	Bullets(glm::vec2 position,glm::vec2 direction,float damage , float speed);
	~Bullets();

	void update(std::vector<Animal*>& animals,
		std::vector <Poachers*>& poachers);

	void draw(GameEngine::SpriteBatch& spriteBatch);


private:
	float _damage;
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
};


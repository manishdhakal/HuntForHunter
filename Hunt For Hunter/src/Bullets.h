#pragma once

#include<glm.hpp>
#include<vector>
#include<SpriteBatch.h>
class Agent;
class Animal;
class Poachers;

const int BULLET_RADIUS=5;

class Bullets
{
public:
	Bullets(glm::vec2 position,glm::vec2 direction,float damage , float speed);
	~Bullets();

	bool update(const std::vector<std::string>& levelData);

	void draw(GameEngine::SpriteBatch& spriteBatch);

	bool collideWithAgent(Agent* agent);

	float getDamage() const
	{
		return _damage;
	}

private:

	bool collideWithWorld(const std::vector<std::string>& levelData);

	float _damage;
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
};


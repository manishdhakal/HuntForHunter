#include "Bullets.h"
#include"ResourceManager.h"
#include"Agent.h"
#include"Animal.h"
#include"Poachers.h"
#include"Level.h"
Bullets::Bullets(glm::vec2 position, glm::vec2 direction, float damage, float speed):
	_position(position),
	_direction(direction),
	_damage(damage),
	_speed(speed)

{
}


Bullets::~Bullets()
{
}

bool Bullets::update(const std::vector<std::string>& levelData)
{
	_position += _direction * _speed;
	return collideWithWorld(levelData);

}

void Bullets::draw(GameEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 destRect(_position.x + BULLET_RADIUS,
		_position.y + BULLET_RADIUS,
		BULLET_RADIUS*2,
		BULLET_RADIUS*2);
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	spriteBatch.draw(destRect, uvRect, GameEngine::ResourceManager::getTexture("textures/bullet.png").id, 0.0f, color);
}

bool Bullets::collideWithAgent(Agent* agent)
{
	const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;

	glm::vec2 centerPosAgent1 = _position;
	glm::vec2 centerPosAgent2 = agent->getposition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosAgent1 - centerPosAgent2;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0)
	{

		//glm::vec2 collisionDepthVec = glm::normalize(distVec)* collisionDepth;

		
		return true;
	}
	return false;

}

bool Bullets::collideWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	if (gridPosition.x < 0 || gridPosition.x >= levelData[0].size() ||
		gridPosition.y < 0 || gridPosition.y >= levelData.size())
	{
		return true;
	}

	return (levelData[gridPosition.y][gridPosition.x] != '.');


}
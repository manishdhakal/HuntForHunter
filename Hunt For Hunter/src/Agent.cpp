#include "Agent.h"
#include"Level.h"
#include"ResourceManager.h"
#include<algorithm>
#include<iostream>
Agent::Agent()
{
}


Agent::~Agent()
{
}

bool Agent::CollideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePositions;
	
	checkTilePosition(levelData,
		collideTilePositions,
		_position.x,
		_position.y);

	checkTilePosition(levelData,
		collideTilePositions,
		_position.x+AGENT_WIDTH,
		_position.y);

	checkTilePosition(levelData,
		collideTilePositions,
		_position.x,
		_position.y+ AGENT_WIDTH);

	checkTilePosition(levelData,
		collideTilePositions,
		_position.x+ AGENT_WIDTH,
		_position.y+ AGENT_WIDTH);

	if (collideTilePositions.size() == 0)
	{
		return false;
	}

	for (int i = 0; i < collideTilePositions.size(); i++)
	{
		collideWithTile(collideTilePositions[i]);
	}
	return true;

}

bool Agent::collideWithAgent(Agent* agent)
{
	
	const float MIN_DISTANCE = AGENT_RADIUS * 2.0f;

	glm::vec2 centerPosAgent1 = _position + glm::vec2(AGENT_WIDTH / 2);
	glm::vec2 centerPosAgent2 = agent->getposition() + glm::vec2(AGENT_WIDTH / 2);

	glm::vec2 distVec = centerPosAgent1 - centerPosAgent2;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0)
	{

		glm::vec2 collisionDepthVec = glm::normalize(distVec)* collisionDepth;

		_position += collisionDepthVec / 2.0f;
		agent->_position -= collisionDepthVec / 2.0f;
		return true;
	}
	return false;

}

void Agent::draw(GameEngine::SpriteBatch& _spriteBatch, int i)
{
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	int textureID;
	if (i == 0)
		textureID = GameEngine::ResourceManager::getTexture(std::string("textures/sprites/") + spriteFile).id;
	else if (i >= 5 && i <= 10)
		textureID = GameEngine::ResourceManager::getTexture("textures/boar.png").id;
	else if (i >= 11 && i <= 15)
		textureID = GameEngine::ResourceManager::getTexture("textures/lion.png").id;
	else if (i >= 16 && i <= 20)
		textureID = GameEngine::ResourceManager::getTexture("textures/giraffe.png").id;
	else if (i >= 21 && i <= 25)
		textureID = GameEngine::ResourceManager::getTexture("textures/tiger.png").id;
	else if (i >= 21 && i <= 25)
		textureID = GameEngine::ResourceManager::getTexture("textures/zebra.png").id;
	else if (i >= 26 && i <= 35)
		textureID = GameEngine::ResourceManager::getTexture("textures/rhino.png").id;
	else if (i >= 36 && i <= 40)
		textureID = GameEngine::ResourceManager::getTexture("textures/panther.png").id;
	else if (i >= 41 && i <= 45)
		textureID = GameEngine::ResourceManager::getTexture("textures/bear.png").id;
	else
		textureID = GameEngine::ResourceManager::getTexture("textures/fox.png").id;


	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;
	
	_spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}

void Agent::draw(GameEngine::SpriteBatch& _spriteBatch)
{
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	int textureID = GameEngine::ResourceManager::getTexture("textures/po.png").id;
	

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;
	_spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}

bool Agent::applyDamage(float damage)
{
	_health -= damage;
	if (_health <= 0)
	{
		return true;
	}

	return false;
}




void Agent::checkTilePosition(const std::vector<std::string>& levelData,
								std::vector<glm::vec2>& collideTilePositions,
								float x,
								float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));

	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].size() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size())
	{
		return;
	}

	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{
		collideTilePositions.push_back(cornerPos*(float)TILE_WIDTH+glm::vec2((float)TILE_WIDTH/2.0f));

	}
}


void Agent::collideWithTile(glm::vec2 tilePos)
{
	const float TILE_RADIUS= (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;
	glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float xDepth = MIN_DISTANCE - abs(distVec.x);

	float yDepth = MIN_DISTANCE - abs(distVec.y);

	

	if (xDepth > 0 && yDepth > 0)
	{
		if (std::max(xDepth,0.0f) < std:: max(yDepth, 0.0f))
		{
			if (distVec.x < 0)
			{
				_position.x -= xDepth;
			}
			else
			{
				_position.x += xDepth;
			}
		}
		else
		{
			if (distVec.y < 0)
			{
				_position.y -= yDepth;
			}
			else
			{
				_position.y += yDepth;
			}

		}
	}

}

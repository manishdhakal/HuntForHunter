#pragma once
#include<glm.hpp>
#include"SpriteBatch.h"
#include <string>
//#include"Vertex.h"
const float AGENT_WIDTH = 60;

class Poachers;
class Animal;



class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Animal*>& animals,
		std::vector <Poachers*>& poachers)=0;

	void CollideWithLevel(const std::vector<std::string>& levelData);

	void draw( GameEngine::SpriteBatch& _spriteBatch, int i);
//	void draw(GameEngine::SpriteBatch& _spriteBatch, int i = 0);


	glm::vec2 getposition() const
	{
		return _position;
	}

protected:

	
	void checkTilePosition(const std::vector<std::string>& levelData,
							std::vector<glm::vec2>& collideTilePosition,
							float x,
							float y );

	void collideWithTile(glm::vec2 tilePos);

	glm::vec2 _position;
	GameEngine::Color _color;
	float _speed;
	std::string spriteFile;



};


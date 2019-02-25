#pragma once
#include<glm.hpp>
#include"SpriteBatch.h"
//#include"Vertex.h"
const float AGENT_WIDTH = 60;

class Agent
{
public:
	Agent();
	virtual ~Agent();

	void draw( GameEngine::SpriteBatch& _spriteBatch);

protected:
	glm::vec2 _position;
	GameEngine::Color _color;
	float _speed;



};


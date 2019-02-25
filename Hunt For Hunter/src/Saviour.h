#pragma once
#include"Animal.h"
#include"keyHandler.h"
class Saviour:public Animal
{
public:
	Saviour();
	~Saviour();

	void init(float speed,glm::vec2 pos, GameEngine::keyHandler* _keyHandler);

	void update();
private:
	GameEngine::keyHandler* _keyHandler;

};


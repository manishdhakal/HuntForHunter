#pragma once
#include"Animal.h"
#include"keyHandler.h"
class Saviour:public Animal
{
public:
	Saviour();
	~Saviour();

	void init(int speed,glm::vec2 pos);

	void update(GameEngine::keyHandler& keyHandler);
};


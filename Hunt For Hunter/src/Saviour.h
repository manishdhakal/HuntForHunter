#pragma once
#include"Animal.h"
#include"keyHandler.h"
class Saviour:public Animal
{
public:
	Saviour();
	~Saviour();

	void init(float speed,glm::vec2 pos, GameEngine::keyHandler* keyHandler);

	void update(const std::vector<std::string>& levelData,
		std::vector<Animal*>& animals,
		std::vector <Poachers*>& poachers);
private:
	GameEngine::keyHandler* _keyHandler;

};


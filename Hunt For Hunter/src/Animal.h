#pragma once
#include"Agent.h"
class Animal:public Agent
{
public:
	Animal();
	virtual ~Animal();

	void init(float speed, glm::vec2 pos);

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Animal*>& animals,
		std::vector <Poachers*>& poachers);
	

private:
	glm::vec2 _direction;


};


#pragma once
#include"Agent.h"


class Poachers:public Agent
{
public:
	Poachers();
	~Poachers();

	void init(float speed,glm::vec2 pos);

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Animal*>& animals,
		std::vector <Poachers*>& poachers);
private:
	Animal* getNearestAnimal(std::vector<Animal*>& animals);




};


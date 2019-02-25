#pragma once
#include"Agent.h"
class Poachers:public Agent
{
public:
	Poachers();
	~Poachers();

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Animal*>& animals,
		std::vector <Poachers*>& poachers);

};


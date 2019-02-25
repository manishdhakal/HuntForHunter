#pragma once
#include"Agent.h"
class Animal:public Agent
{
public:
	Animal();
	virtual ~Animal();

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Animal*>& animals,
		std::vector <Poachers*>& poachers);


};


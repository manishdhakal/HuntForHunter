#pragma once
#include <string>
#include <vector>
class Level
{
public:
	Level(const std::string &filename);
	~Level();

private:
	std::vector<std::string> _leveldata;
	int _numhumans;

};


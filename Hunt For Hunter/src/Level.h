#pragma once
#include <string>
#include <vector>
#include <SpriteBatch.h>
//#include<ResourceManager.h>
const int TILE_WIDTH = 64;
class Level
{
public:
	Level(const std::string &filename);
	~Level();

	void draw();

private:
	std::vector<std::string> _leveldata;
	int _numhumans;
	GameEngine::SpriteBatch _spriteBatch;

	//GameEngine::ResourceManager* resourceManager;
	glm::ivec2 _startPlayerPos;
	std::vector<glm::ivec2> _zombieStartPosition;
};


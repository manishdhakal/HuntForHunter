#pragma once
#include <string>
#include <vector>
#include <SpriteBatch.h>
const int TILE_WIDTH = 64;
class Level
{
public:
	Level(const std::string &filename);
	~Level();

	void draw();
	int getWidth() const
	{
		return _leveldata[0].size();
	}

	int getHeight() const
	{
		return _leveldata.size();
	}

	int getNumAnimals() const
	{
		return _numAnimals;
	}

	const std::vector<std::string>& getLevelData() const
	{
		return _leveldata;
	}

	glm::vec2 getStartSaviourPos() const
	{
		return _startSaviourPos;
	}

	const std::vector<glm::vec2>& getStartPoacherPos() const
	{
		return _poacherStartPosition;
	}

private:
	std::vector<std::string> _leveldata;
	int _numAnimals;
	GameEngine::SpriteBatch _spriteBatch;
	glm::ivec2 _startSaviourPos;
	std::vector<glm::vec2> _poacherStartPosition;
};


#include "Level.h"
#include <fstream>
#include <Common.h>



Level::Level(const std::string &fileName)
{
	
	std::ifstream file;
	file.open(fileName);

	
	if (file.fail()) {
		GameEngine::Error(4,"Failed to open " + fileName,"Unable to open file");
	}
	std::string temp;
	file >> temp >> _numhumans;
	while (std::getline(file, temp))
	{

     _leveldata.push_back(temp);
	}


	for (int i = 0; i < _leveldata.size(); i++)
	{

		std::cout << _leveldata[i] << std::endl;
    }

}


Level::~Level()
{
}

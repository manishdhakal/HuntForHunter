#include "keyHandler.h"


namespace GameEngine {
	keyHandler::keyHandler()
	{
	}


	keyHandler::~keyHandler()
	{
	}

	void keyHandler::keyPress(unsigned int keyID) {
		keyMap[keyID] = true;
	}

	void keyHandler::keyRelease(unsigned int keyID) {
		keyMap[keyID] = false;
	}

   	bool keyHandler::iskeyPressed(unsigned int keyID) {
		if (keyMap.empty()) return false;
		const auto& it = keyMap.find(keyID);
		if (it != keyMap.end())
			return it->second;
		else
			return false;  
	}

	void keyHandler::setMouseCoordinates(float x, float y) {
		mouseCoordinates.x = x;
		mouseCoordinates.y = y;
	}
}
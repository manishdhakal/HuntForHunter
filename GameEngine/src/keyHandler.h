#pragma once
#include <unordered_map>
#include "glm.hpp"
//equivalent of InputManager...
namespace GameEngine {
	class keyHandler
	{
	public:
		keyHandler();
		~keyHandler();

		void keyPress(unsigned int keyID);
		void keyRelease(unsigned int keyID);
		bool iskeyPressed(unsigned int keyID);
		
		void setMouseCoordinates(float x, float y);

		const inline glm::vec2 getMouseCoordinates() { return mouseCoordinates; }

	private:
		std::unordered_map<unsigned int, bool> keyMap;
		glm::vec2 mouseCoordinates;
	};

}
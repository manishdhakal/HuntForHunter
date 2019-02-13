#pragma once
#include<SDL.h>
#include<glew.h>
#include<string>

namespace GameEngine
{
	enum Windowflags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Windows
	{
	public:
		Windows();
		~Windows();
		int create(std::string WindowName, int ScreenWidth, int ScreenHeight, unsigned int currentFlags);
		int getScreenWidth()
		{
			return _screenWidth;
		}
		int getScreenHeight()
		{
			return _screenHeight;
		}
		void swapBuffer();
	private:
		SDL_Window* _sdlWindow;
		int _screenWidth, _screenHeight;
	};
}

#pragma once
#include <SDL.h>


#include "sprites.h"

 enum class GameState {PLAY,EXIT}; 
class maingame
{
public:
	maingame();
	~maingame();
	void run();
private:
	
	void initSystems();
	//void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	sprites _sprite;
};


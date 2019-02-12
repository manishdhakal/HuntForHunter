#pragma once
#include <SDL.h>
#include "GLSLProgram.h"
#include<vector>
#include "sprites.h"
#include "texture.h"

 enum class GameState {PLAY,EXIT}; 
class maingame
{
public:
	maingame();
	~maingame();
	void run();
private:
	
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	
	int _screenWidth;
	int _screenHeight;
	float _time;
	SDL_Window* _window;
	GameState _gameState;
	//GLTexture _texture;
	//sprites _sprite;
	std::vector <sprites*> _sprites;
	GLSLProgram _colorProgram;
};


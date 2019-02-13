#pragma once
#include <SDL.h>
#include"GameEngine.h"
#include "GLSLProgram.h"
#include<vector>
#include "sprites.h"
#include "texture.h"
#include"Windows.h"

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
	void calculateFPS();
	
	int _screenWidth;
	int _screenHeight;
	float _time;
	GameEngine::Windows _window;
	GameState _gameState;
	//GLTexture _texture;
	//sprites _sprite;
	std::vector <GameEngine::sprites*> _sprites;
	GameEngine::GLSLProgram _colorProgram;
	float _fps;
	float _maxFPS;
	float _frameTime;
	
};


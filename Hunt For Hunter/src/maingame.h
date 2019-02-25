#pragma once
#include <SDL.h>
#include"GameEngine.h"
#include "GLSLProgram.h"
#include <vector>
#include "sprites.h"
#include "texture.h"
#include "Windows.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "keyHandler.h"
#include "timing.h"
//#include "fireWeapon.h"
#include "Level.h"

#include"Saviour.h"

 enum class GameState {PLAY,EXIT}; 
class maingame
{
public:
	maingame();
	~maingame();
	void run();
private:
	
	void initSystems();
	void initLevel();

	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	
	int _screenWidth;
	int _screenHeight;


	float _time;
	GameEngine::Windows _window;
	
	
	GameEngine::GLSLProgram _textureProgram;


	GameEngine::Camera2D camera;

	GameEngine::SpriteBatch _agentSpriteBatch;

	GameEngine::SpriteBatch _spriteBatch;

	GameEngine::keyHandler keyHandlerObj;
	
	std::vector<Level*> _levels;

	int _fps;
	
	int _currentLevel;

	Saviour* _saviour;
	std::vector<Animal*> _animals;

	GameState _gameState;
	
};


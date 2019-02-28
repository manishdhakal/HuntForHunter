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
#include "Level.h"
#include"Bullets.h"
#include"Saviour.h"

class Poachers;

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

	void updateAgents();

	void updateBullets();

	void checkVictory();


	void processInput();
	void drawGame();
	
	void readHighscore();
	void saveHighscore();
	
	int _screenWidth;
	int _screenHeight;


	int _numAnimalsKilled;
	int _numPoachersKilled;

	int prevHighscore;

	float _time;
	float _fps;

	int _currentLevel;

	GameEngine::Windows _window;
	
	GameEngine::GLSLProgram _textureProgram;

	GameEngine::Camera2D camera;

	GameEngine::SpriteBatch _agentSpriteBatch;

	GameEngine::SpriteBatch _spriteBatch;

	GameEngine::keyHandler _keyHandler ;
	
	std::vector<Level*> _levels;

	Saviour* _saviour;
	std::vector<Animal*> _animals;
	std::vector<Poachers*> _poachers;

	std::vector<Bullets> _bullets;

	GameState _gameState;
	
};


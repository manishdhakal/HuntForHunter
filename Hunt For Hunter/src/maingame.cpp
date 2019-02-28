#include "maingame.h"
#include "Common.h"
#include <iostream>
#include <string>
#include <timing.h>
#include "glm.hpp"
#include<random>
#include<ctime>
#include"Poachers.h"

#include"Gun.h"

#include <fstream>

const float ANIMAL_SPEED = 1.0f;
const float POACHER_SPEED = 1.3f;

maingame::maingame() :
	_screenWidth(1024),
	_screenHeight(768),
	_fps(0),
	_saviour(nullptr),
	_numAnimalsKilled(0),
	_numPoachersKilled(0),
	_gameState(GameState::PLAY)
	
{}

maingame::~maingame()
{
	for (int i = 0; i < _levels.size(); i++)
	{
		delete _levels[i];
	}
}

void maingame::run()
{
	initSystems();
	initLevel();
	gameLoop();
}

void maingame::initSystems()
{
	GameEngine::init();
	_window.create("Hunt For  Hunter", _screenWidth, _screenHeight,0);
	glClearColor(0.0f, 0.41f, 0.0f, 0.0f);
	initShaders();

	_agentSpriteBatch.init();
	
	camera.init(_screenWidth, _screenHeight);
}

void maingame::initLevel()
{
	_levels.push_back(new Level("Levels/level1.txt"));

	_currentLevel = 0;
	_saviour = new Saviour();
	_saviour->init(4.0f, _levels[_currentLevel]->getStartSaviourPos(), &_keyHandler,&camera,&_bullets);

	_animals.push_back(_saviour);

	 std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	 std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
	 std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

	for (int i = 0; i < _levels[_currentLevel]->getNumAnimals(); i++)
	{
		_animals.push_back(new Animal);
		glm::vec2 pos(randX(randomEngine)*TILE_WIDTH, randY(randomEngine)*TILE_WIDTH);
		_animals.back()->init(ANIMAL_SPEED, pos);
	}

	const std::vector<glm::vec2>& poacherPositions = _levels[_currentLevel]->getStartPoacherPos();
	for (int i = 0; i < poacherPositions.size(); i++)
	{
		_poachers.push_back(new Poachers);
		//glm::vec2 pos(randX(randomEngine)*TILE_WIDTH, randY(randomEngine)*TILE_WIDTH);
		_poachers.back()->init(POACHER_SPEED, poacherPositions[i]);

	}
	const float BULLET_SPEED = 20.0f;
	_saviour->addGun(new Gun("Magnum", 10, 1, 5.0f, 30, BULLET_SPEED));
	_saviour->addGun(new Gun("Shotgun", 30, 12, 20.0f, 4, BULLET_SPEED));
	_saviour->addGun(new Gun("MP5", 2, 1, 10.0f, 20, BULLET_SPEED));
}

void maingame::initShaders()
{
	_textureProgram.compileShaders("shaders/colorShading.vert.txt", "shaders/colorShading.frag.txt");
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");
	_textureProgram.linkShaders();
}

void maingame::gameLoop()
{
	GameEngine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(60.0f);
	while (_gameState == GameState::PLAY)
    {
		fpsLimiter.beginFrame();
		
		checkVictory();

		processInput();
		updateAgents();

		updateBullets();

		camera.setPosition(_saviour->getposition());

		camera.update();
		drawGame();

		 _fps = fpsLimiter.endFrame();
	}
}

void maingame::updateAgents()
{
	//Update all the animals
	for (int i = 0; i < _animals.size(); i++)
	{
		_animals[i]->update(_levels[_currentLevel]->getLevelData(),
			_animals,
			_poachers);
	}

	//Update all the poachers
	for (int i = 0; i < _poachers.size(); i++)
	{
		_poachers[i]->update(_levels[_currentLevel]->getLevelData(),
			_animals,
			_poachers);
	}

	//Update poacher collision
	for (int i = 0; i < _poachers.size(); i++)
	{
		//collide with other poachers
		for (int j = i + 1; j < _poachers.size(); j++)
		{
			_poachers[i]->collideWithAgent(_poachers[j]);
		}
		//collide with animals
		for (int j = 1; j < _animals.size(); j++)
		{
			if (_poachers[i]->collideWithAgent(_animals[j]))
			{
				delete _animals[j];
				_animals[j] = _animals.back();
				_animals.pop_back();
			}
		}
		//Collision of saviour and poachers 
		if (_poachers[i]->collideWithAgent(_saviour))
		{
			char key = ' ';
			std::cout << "!!! YOU LOOSE !!!"<<std::endl<<"You were captured by poachers and cannot save the protected area(Jungle)" << std::endl;
			while (key != 'q') {
				std::cout << "Press 'q' to Quit." << std::endl;
				std::cin >> key;
				if (key == 'q')
					exit(69);
			}
		}

	}

	//Update animals collision

	for (int i = 0; i < _animals.size(); i++)
	{
		// Collide with other animals
		for (int j = i+1; j < _animals.size(); j++)
		{
			_animals[i]->collideWithAgent(_animals[j]);
		}
	}

}

void  maingame::updateBullets()
{
	//Update and collide with world
	for (int i = 0; i < _bullets.size(); )
	{
		if (_bullets[i].update(_levels[_currentLevel]->getLevelData()))
		{
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else 
			i++;
	}

	bool wasBulletRemoved;

	//Collide with animals and poachers
	for (int i = 0; i < _bullets.size();i++ )
	{

		wasBulletRemoved = false;

		//Loop through poachers
		for (int j = 0; j < _poachers.size(); )
		{
			if (_bullets[i].collideWithAgent(_poachers[j]))
			{

				//Kill the poacher if it is out of health
				if (_poachers[j]->applyDamage(_bullets[i].getDamage()))
				{
					//Remove the poacher if dead
					delete _poachers[j];
					_poachers[j] = _poachers.back();
					_poachers.pop_back();
					_numPoachersKilled++;
					
				}
				else
				{
					j++;
				}

				//Remove the bullet
				_bullets[i] = _bullets.back();
				_bullets.pop_back();

				wasBulletRemoved = true;
				i--; //We don't skip any bullet 

				//Since the bullet is dead
				break;
			}
			else
			{
				j++;
			}
		}
		

		//Loop through animals
		if (wasBulletRemoved == false)
		{
			for (int j = 1; j < _animals.size(); )
			{
				//check collision
				if (_bullets[i].collideWithAgent(_animals[j]))
				{

					//Kill the animal if it is out of health
					if (_animals[j]->applyDamage(_bullets[i].getDamage()))
					{
						//Remove the animal if dead
						delete _animals[j];
						_animals[j] = _animals.back();
						_animals.pop_back();

					}
					else
					{
						j++;
					}

					//Remove the bullet
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					_numAnimalsKilled++;
					i--; //We don't skip any bullet 

					//Since the bullet is dead
					break;
				}
				else
				{
					j++;
				}
			}

		}

	}

}

void maingame::checkVictory()
{
	if (_poachers.empty())
	{
		readHighscore();

		if (_animals.size() - 1 > prevHighscore)
			saveHighscore();

		std::cout << "!!! YOU WIN !!!"<<std::endl<<"You saved the jungle from all the poachers" << std::endl;
		std::printf("You killed %d Animals and %d poachers.\nThere are %d/%d Animals remaining.",
			_numAnimalsKilled,_numPoachersKilled,_animals.size()-1,_levels[_currentLevel]->getNumAnimals());
		std::cout << "Press Enter to Quit." << std::endl;
		char key =  ' ';
		while (key != 'q') {
			std::cout << "Press 'q' to Quit." << std::endl;
			std::cin >> key;
			if (key == 'q')
				exit(69);
		}
	}

	if (_animals.size() == 1)
	{
		std::cout << "!!! YOU LOOSE !!!" << std::endl << "You couldn't save the animals of jungle" << std::endl;
		std::printf("You killed %d Animals and %d poachers.\nThere are %d Poachers remaining.",
			_numAnimalsKilled, _numPoachersKilled, _poachers.size());
		std::cout << "Press Enter to Quit." << std::endl;
		char key = ' ';
		while (key != 'q') {
			std::cout << "Press 'q' to Quit." << std::endl;
			std::cin >> key;
			if (key == 'q')
				exit(69);
		}
	}
}

void maingame::processInput()
{
	SDL_Event evnt;
	const float CameraSpeed = 20.0f;
	const float ScaleSpeed = 0.05f;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_keyHandler.setMouseCoordinates(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_KEYDOWN:
				_keyHandler.keyPress(evnt.key.keysym.sym);
				break;
			case  SDL_KEYUP:
				_keyHandler.keyRelease(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_keyHandler.keyPress(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_keyHandler.keyRelease(evnt.button.button);
				break; 
		}
	}

	if (_keyHandler.iskeyPressed( SDLK_w))
		camera.setPosition(camera.getPosition() + glm::vec2(0.0f, CameraSpeed));

	if (_keyHandler.iskeyPressed( SDLK_s))
		camera.setPosition(camera.getPosition() - glm::vec2(0.0f, CameraSpeed));
	
	if (_keyHandler.iskeyPressed( SDLK_a))
		camera.setPosition(camera.getPosition() + glm::vec2(-CameraSpeed, 0.0f));
	if (_keyHandler.iskeyPressed( SDLK_d))
		camera.setPosition(camera.getPosition() + glm::vec2(CameraSpeed, 0.0f));
		
	if (_keyHandler.iskeyPressed( SDLK_EQUALS))
		camera.setScale(camera.getScale() + ScaleSpeed);
		
	if (_keyHandler.iskeyPressed(SDLK_MINUS)) {
		if (camera.getScale() > 0.5)
			camera.setScale(camera.getScale() - ScaleSpeed);
	}
	
}

void maingame:: drawGame()
{
	

	GLError(glClearDepth(1.0));
	GLError(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = camera.getcameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");

	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	_levels[_currentLevel]->draw();

	_agentSpriteBatch.begin();

	for (int i = 0; i < _animals.size(); i++)
	{
		_animals[i]->draw(_agentSpriteBatch, i);
	}

	for (int i = 0; i < _poachers.size(); i++)
	{
		_poachers[i]->draw(_agentSpriteBatch);
	}

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_agentSpriteBatch);
	}

	_agentSpriteBatch.end();



	_agentSpriteBatch.renderBatch();
	_textureProgram.unuse();

	_window.swapBuffer();  

}


void maingame::readHighscore() {

	std::string scorestring;

	std::ifstream ScoreFile("score/highscore", std::ifstream::in);
	getline(ScoreFile, scorestring);
	prevHighscore = std::stoi(scorestring);

	ScoreFile.close();
}
void maingame::saveHighscore() {

	std::ofstream Highscorefile("score/highscore", std::ofstream::out);
	Highscorefile << _animals.size() << std::endl;

	Highscorefile.close();
}

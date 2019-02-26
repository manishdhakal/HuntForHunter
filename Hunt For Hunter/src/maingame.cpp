#include "maingame.h"
#include "Common.h"
#include <iostream>
#include <string>
#include <timing.h>
#include"GameEngine.h"
#include "glm.hpp"
#include<random>
#include<ctime>
#include"Poachers.h"
maingame::maingame() :
	_screenWidth(1024),
	_screenHeight(768),
	_fps(0),
	_saviour(nullptr),
	_gameState(GameState::PLAY)
	
{
	
	
}


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
	_saviour->init(4.0f, _levels[_currentLevel]->getStartSaviourPos(), &_keyHandler);

	_animals.push_back(_saviour);

	 std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	 std::uniform_int_distribution<int> randX(1, _levels[_currentLevel]->getWidth() - 2);
	 std::uniform_int_distribution<int> randY(1, _levels[_currentLevel]->getHeight() - 2);

	 const float ANIMAL_SPEED = 1.0f;
	for (int i = 0; i < _levels[_currentLevel]->getNumAnimals(); i++)
	{
		_animals.push_back(new Animal);
		glm::vec2 pos(randX(randomEngine)*TILE_WIDTH, randY(randomEngine)*TILE_WIDTH);
		_animals.back()->init(ANIMAL_SPEED, pos);


	}


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

		processInput();
		//_saviour->update();
		updateAgents();
		camera.setPosition(_saviour->getposition());

		camera.update();
		drawGame();


		 _fps=fpsLimiter.endFrame();



	}
	/*while (_gameState != GameState::EXIT)
	{
		fpsLimiterObj.beginFrame();
		
		processInput();

		_time += 0.01;

		camera.update();

		for (int i = 0; i < bullets.size(); i++) {

			if (bullets[i].updatePos() == true) {
				bullets[i] = bullets.back();
				bullets.pop_back();
			}
			else {
				i++;
			}
		}

		drawGame();
		_fps = fpsLimiterObj.endFrame();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10000)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;

		}

	} */
}

void maingame::updateAgents()
{
	for (int i = 0; i < _animals.size(); i++)
	{
		_animals[i]->update(_levels[_currentLevel]->getLevelData(),
			_animals,
			_poachers);
	}
}


void maingame::processInput()
{
	SDL_Event evnt;
	const float CameraSpeed = 20.0f;
	const float ScaleSpeed = 0.1f;

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
		
	if (_keyHandler.iskeyPressed( SDLK_q))
		camera.setScale(camera.getScale() + ScaleSpeed);
		
	if (_keyHandler.iskeyPressed(SDLK_p))
		camera.setScale(camera.getScale() - ScaleSpeed);

	/*if (keyHandlerObj.iskeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoordinates = keyHandlerObj.getMouseCoordinates();
		mouseCoordinates = camera.ScreenToWorldCoordinates(mouseCoordinates);
		std::cout << mouseCoordinates.x << "  " << mouseCoordinates.y << '\n';

		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoordinates - playerPosition;
		
		direction = glm::normalize(direction);

		bullets.emplace_back(playerPosition, direction, 5.0f, 1000);
	}  */
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
	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();
	_textureProgram.unuse();

	_window.swapBuffer();  

}


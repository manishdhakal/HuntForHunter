#include "maingame.h"
#include "Common.h"
#include <iostream>
#include <string>
#include <timing.h>
#include"GameEngine.h"
#include "glm.hpp"

maingame::maingame() :
	_screenWidth(1024),
	_screenHeight(768),
	_fps(0),
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
	gameLoop();
	
}
void maingame::initSystems()
{
	GameEngine::init();
	_window.create("Hunt For  Hunter", _screenWidth, _screenHeight,0);
	//glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	initShaders();
	
	_levels.push_back(new Level("Levels/level1.txt"));

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

		//processInput();

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

void maingame::processInput()
{
	/*SDL_Event evnt;
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
				keyHandlerObj.setMouseCoordinates(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_KEYDOWN:
				keyHandlerObj.keyPress(evnt.key.keysym.sym);
				break;
			case  SDL_KEYUP:
				keyHandlerObj.keyRelease(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				keyHandlerObj.keyPress(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				keyHandlerObj.keyRelease(evnt.button.button);
				break; 
		}
	}

	if (keyHandlerObj.iskeyPressed( SDLK_w))
		camera.setPosition(camera.getPosition() + glm::vec2(0.0f, CameraSpeed));

	if (keyHandlerObj.iskeyPressed( SDLK_s))
		camera.setPosition(camera.getPosition() - glm::vec2(0.0f, CameraSpeed));
	
	if (keyHandlerObj.iskeyPressed( SDLK_a))
		camera.setPosition(camera.getPosition() + glm::vec2(-CameraSpeed, 0.0f));
	if (keyHandlerObj.iskeyPressed( SDLK_d))
		camera.setPosition(camera.getPosition() + glm::vec2(CameraSpeed, 0.0f));
		
	if (keyHandlerObj.iskeyPressed( SDLK_q))
		camera.setScale(camera.getScale() + ScaleSpeed);
		
	if (keyHandlerObj.iskeyPressed(SDLK_p))
		camera.setScale(camera.getScale() - ScaleSpeed);

	if (keyHandlerObj.iskeyPressed(SDL_BUTTON_LEFT)) {
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
	/*
	_colorProgram.use();
	GLError(glActiveTexture(GL_TEXTURE0));
	//glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	GLError(glUniform1i(textureLocation, 0));
	
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 CameraMatrix = camera.getcameraMatrix();

	GLError(glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(CameraMatrix[0][0])));

	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	GLError(static GameEngine::GLTexture texture = GameEngine::ResourceManager::getTexture("textures/player.png"));
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);  
	//_spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].draw(_spriteBatch);
	}
	
	
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	
	GLError(glBindTexture(GL_TEXTURE_2D,0));
	_colorProgram.unuse();*/
	_window.swapBuffer();  

}


#include "maingame.h"
#include "Common.h"
#include <iostream>
#include <string>
#include"glm.hpp"
#include"ResourceManager.h"

maingame::maingame() :
	_screenWidth(1024),
	_screenHeight(768),
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
	camera.init(_screenWidth, _screenHeight);
	
}


maingame::~maingame()
{
}
void maingame::run()
{
	initSystems();
	
	gameLoop();

}
void maingame::initSystems()
{
	GameEngine::init();
	_window.create("Game Engine", _screenWidth, _screenHeight,0);

	initShaders();
	_spriteBatch.init();

}
void maingame::initShaders()
{
	_colorProgram.compileShaders("shaders/colorShading.vert.txt", "shaders/colorShading.frag.txt");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}


void maingame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		float startTicks = SDL_GetTicks();
		processInput();
		_time += 0.01;
		camera.update();
		drawGame();
		calculateFPS();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;

		}
		float  frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFPS > frameTicks)
		{
			SDL_Delay(1000.0f/_maxFPS-frameTicks);
		}
		
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
			//std::cout << evnt.motion.x << " " << evnt.motion.y <<std:: endl;
			break;
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym)
			{
			case SDLK_w:
				camera.setPosition(camera.getPosition() + glm::vec2(0.0f, CameraSpeed));
				break;
			case SDLK_s :
				camera.setPosition(camera.getPosition() - glm::vec2(0.0f, CameraSpeed));
				break;
			case SDLK_a:
				camera.setPosition(camera.getPosition() + glm::vec2(-CameraSpeed, 0.0f));
				break;
			case SDLK_d:
				camera.setPosition(camera.getPosition() + glm::vec2(CameraSpeed, 0.0f));
				break;
			case SDLK_q:
				camera.setScale(camera.getScale() + ScaleSpeed);
				break;
			case SDLK_p:
				camera.setScale(camera.getScale() - ScaleSpeed);
				break;

			}
			break;
		}
	}
}

void maingame:: drawGame()
{

	GLError(glClearDepth(1.0));
	GLError(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	_colorProgram.use();
	GLError(glActiveTexture(GL_TEXTURE0));
	//glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	GLError(glUniform1i(textureLocation, 0));
	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	GLError(glUniform1f(timeLocation, _time));

	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 CameraMatrix = camera.getcameraMatrix();

	GLError(glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(CameraMatrix[0][0])));

	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	GLError(GameEngine::GLTexture texture = GameEngine::ResourceManager::getTexture("textures/screenshot2_0.png"));
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

	_spriteBatch.end();
	_spriteBatch.renderBatch();



	
	GLError(glBindTexture(GL_TEXTURE_2D,0));
	_colorProgram.unuse();
	_window.swapBuffer();

}

void maingame::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;
	static float prevTicks = SDL_GetTicks();
	float currentTicks;
	currentTicks = SDL_GetTicks();
	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame%NUM_SAMPLES]=_frameTime;
	prevTicks = currentTicks;
	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}
	float frameTimeAverage=0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;
	if (frameTimeAverage > 0)
	{
		_fps = 1000.0 / frameTimeAverage;
	}
	else
	{
		_fps = 60.0f;
	}
	
}


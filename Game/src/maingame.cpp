#include "maingame.h"
#include "Common.h"
//#include"ImageLoader.h"
#include <iostream>
#include <string>

maingame::maingame() :
	_screenWidth(1024),
	_screenHeight(768),
	_time(0.0f),
	//_window(nullptr),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
	
}


maingame::~maingame()
{
}
void maingame::run()
{
	initSystems();
	_sprites.push_back(new GameEngine::sprites());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "textures/screenshot2_0.png");

	_sprites.push_back(new GameEngine::sprites());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "textures/screenshot2_0.png");

	_sprites.push_back(new GameEngine::sprites());
	_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "textures/screenshot2_0.png");
	//_sprite.init(-1.0f,-1.0f,2.0f,2.0f,"textures/screenshot2_0.png");
	//_playerTexture = ImageLoader::loadPNG("textures/screenshot2_0.png");
	gameLoop();

}
void maingame::initSystems()
{
	GameEngine::init();
	_window.create("Game Engine", _screenWidth, _screenHeight,0);

	initShaders();
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
		}
	}
}

void maingame:: drawGame()
{

	GLError(glClearDepth(1.0));
	GLError(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	//GLuint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);
	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}
	
	glBindTexture(GL_TEXTURE_2D,0);
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


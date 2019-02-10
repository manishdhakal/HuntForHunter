#include "maingame.h"
#include "Common.h"
#include"ImageLoader.h"
#include <iostream>
#include <string>

maingame::maingame():
	_screenWidth(1024),
	_screenHeight(768),
	_time(0.0f),
	_window(nullptr),
	_gameState(GameState::PLAY)
{
	
}


maingame::~maingame()
{
}
void maingame::run()
{
	initSystems();
	_sprite.init(-1.0f,-1.0f,2.0f,2.0f);
	_playerTexture = ImageLoader::loadPNG("textures/screenshot2_0.png");
	gameLoop();

}
void maingame::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
	{
		Error(ErrorCode::WindowNotCreated, "SDL", " Window could not be created!");
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		Error(ErrorCode::GLContextNotCreated, "SDL", "SDL_GL context could not be created!");
	}
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		Error(ErrorCode::GLEWNotLoaded, "GLEW", "Could not initialize");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
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
		processInput();
		_time += 0.01;
		drawGame();
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
			std::cout << evnt.motion.x << " " << evnt.motion.y <<std:: endl;
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
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	//GLuint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);
	_sprite.draw();
	glBindTexture(GL_TEXTURE_2D,0);
	_colorProgram.unuse();
	SDL_GL_SwapWindow(_window);

}
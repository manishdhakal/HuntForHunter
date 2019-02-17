#include "Windows.h"

#include "Common.h"
namespace GameEngine
{
	Windows::Windows()
	{
	}


	Windows::~Windows()
	{
	}

	int Windows::create(std::string WindowName, int ScreenWidth, int ScreenHeight, unsigned int currentFlags)
	{

		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}


		_sdlWindow = SDL_CreateWindow(WindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, flags);
		if (_sdlWindow == nullptr)
		{
			Error(ErrorCode::WindowNotCreated, "SDL", " Window could not be created!");
		}
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr)
		{
			Error(ErrorCode::GLContextNotCreated, "SDL", "SDL_GL context could not be created!");
		}
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			Error(ErrorCode::GLEWNotLoaded, "GLEW", "Could not initialize");
		}

		std::printf("*** OpenGL Version: %s ***", glGetString(GL_VERSION));

		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

		SDL_GL_SetSwapInterval(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		return 0;
	}

	void  Windows::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}

}
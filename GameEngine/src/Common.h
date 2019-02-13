#pragma once
#include <string>
#include <iostream>
#include <glew.h>
#include <assert.h>
namespace GameEngine
{
	enum ErrorCode
	{
		Sucess,
		WindowNotCreated,
		GLContextNotCreated,
		GLEWNotLoaded,
		Other
	};

	inline int Error(int code, const std::string& msg, const std::string& desc)
	{
		std::cout << "ERROR[" << msg << "]" << " : " << desc << std::endl;
		return code;
	}

	inline std::string GLGetErrorString(unsigned int errorCode)
	{
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  return "Invalid enum";
		case GL_INVALID_VALUE:                 return "Invalid value";
		case GL_INVALID_OPERATION:             return "Invalid operation";
		case GL_OUT_OF_MEMORY:                 return "Out of memory";
		case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid frame buffer operation";
		default: return "Unknown OpenGL error";
		}
	}
}
#define GLError(x) \
x;\
{\
int err = glGetError();\
while (err != GL_NO_ERROR)\
{\
	GameEngine::Error(err, "OpenGL Call", GameEngine::GLGetErrorString(err));\
	__debugbreak();\
	err = glGetError();\
}\
}

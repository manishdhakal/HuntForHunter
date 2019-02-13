#include "GLSLProgram.h"
#include <vector>
#include "Common.h"

#include <fstream>


namespace GameEngine
{
	GLSLProgram::GLSLProgram() :_numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		GLError(_vertexShaderID = glCreateShader(GL_VERTEX_SHADER));
		GLError(_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER));
		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilePath, _fragmentShaderID);



	}
	void GLSLProgram::linkShaders()
	{

		GLError(glAttachShader(_programID, _vertexShaderID));
		GLError(glAttachShader(_programID, _fragmentShaderID));
		GLError(glLinkProgram(_programID));
		GLint isLinked = 0;
		GLError(glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked));
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			GLError(glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength));


			std::vector<char>errorLog(maxLength);
			GLError(glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]));
			GLError(glDeleteProgram(_programID));
			GLError(glDeleteShader(_vertexShaderID));
			GLError(glDeleteShader(_fragmentShaderID));
			std::printf("%s\n", &(errorLog[0]));
		}
		GLError(glDetachShader(_programID, _vertexShaderID));
		GLError(glDetachShader(_programID, _fragmentShaderID));
		GLError(glDeleteShader(_vertexShaderID));
		GLError(glDeleteShader(_fragmentShaderID));
	}

	void GLSLProgram::addAttribute(const std::string& attributeName)
	{
		GLError(glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str()));
	}

	GLuint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
		/*if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform" + uniformName + "not found in shader!");
		}*/
		return location;
	}

	void GLSLProgram::use()
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++)
		{
			GLError(glEnableVertexAttribArray(i));
		}
	}
	void GLSLProgram::unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++)
		{
			GLError(glDisableVertexAttribArray(i));
		}
	}





	void GLSLProgram::compileShader(const std::string& filePath, GLuint id)
	{
		GLError(_programID = glCreateProgram());
		std::ifstream vertexFile(filePath);
		std::string fileContents = "";
		std::string line;
		while (std::getline(vertexFile, line))
		{
			fileContents += line + "\n";
		}
		vertexFile.close();
		const char* contentsPtr = fileContents.c_str();
		GLError(glShaderSource(id, 1, &contentsPtr, nullptr));
		GLError(glCompileShader(id));
		GLint success = 0;
		GLError(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			GLError(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength));
			std::vector<char>errorLog(maxLength);
			GLError(glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]));
			GLError(glDeleteShader(id));

			std::printf("%s\n", &(errorLog[0]));
		}



	}


}
#include "I_ShaderProgram.h"
#include <fstream>

void I_ShaderProgram::printProgramLog(GLuint ID)
{
	//make sure name is shader
	if(glIsProgram(ID))
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//get info string length
		glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &maxLength);

		//allocate string
		char* infoLog = new char[maxLength];

		//get info log
		glGetProgramInfoLog(ID, maxLength, &infoLogLength, infoLog);

		if(infoLogLength > 0)
		{
			printf("printProgramLog: %s\n", infoLog);
		}

		delete[] infoLog;
		infoLog = NULL;
	}

	else
	{
		printf("Name %d is not a program\n", ID);
	}
}

void I_ShaderProgram::printShaderLog(GLuint ID)
{
	if(glIsProgram(ID))
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &maxLength);

		char* infoLog = new char[maxLength];

		glGetProgramInfoLog(ID, maxLength, &infoLogLength, infoLog);

		if(infoLogLength > 0)
		{
			printf("printShaderLog: %s\n", infoLog);
		}

		delete[] infoLog;
		infoLog = NULL;
	}
	
	else
	{
		printf("Name %d is not a shader\n", ID);
	}
}

bool I_ShaderProgram::bind()
{
	glUseProgram(m_ProgramID);

	GLenum error = glGetError();

	if(error != GL_NO_ERROR)
	{
		printf("Error binding shader!%s\n", gluErrorString(error));
		printProgramLog(m_ProgramID);
		return false;
	}

	return true;
}

void I_ShaderProgram::unbind()
{
	glUseProgram(NULL);
}

bool I_ShaderProgram::loadProgram(std::string glvs, std::string glfs)
{
	return _loadProgram(glvs, glfs);
}

GLuint I_ShaderProgram::loadShaderFromFile(std::string path, GLenum shaderType)
{
	GLuint shaderID = 0;
	std::string shaderString;

	//open file
	std::ifstream sourceFile(path.c_str());

	//source file loaded
	if(sourceFile.is_open())
	{
		//get shader source; using an input stream buffer iterator, read as one line
		//first argument: start at beginning of file; second argument: keep reading until reach a null char
		shaderString.assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

		//generate shader ID
		shaderID = glCreateShader(shaderType);

		//set shader source
		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

		//compile shader source
		glCompileShader(shaderID);
		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);

		if(shaderCompiled != GL_TRUE)
		{
			printf("Unable to compile vertex shader %d\n", shaderID);
			printShaderLog(shaderID);
			glDeleteShader(shaderID);
			shaderID = 0;
		}

		sourceFile.close();
	}

	else
	{
		printf("Unable to open file %s\n", path.c_str());
	}

	return shaderID;
}

void I_ShaderProgram::_freeProgram()
{
	if(m_ProgramID != NULL)
	{
		glDeleteProgram(m_ProgramID);
		m_ProgramID = NULL;
	}
}

void I_ShaderProgram::freeProgram()
{
	_freeProgram();
}
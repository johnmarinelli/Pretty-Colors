#ifndef I_SHADERPROGRAM_H
#define I_SHADERPROGRAM_H

#include "_OpenGL.h"
#include <string>

class I_ShaderProgram
{
protected:
	virtual bool _loadProgram(std::string glvs, std::string glfs) = 0;
	virtual void _freeProgram();

	GLuint loadShaderFromFile(std::string path, GLenum shaderType);

	GLuint m_ProgramID;

public:
	bool bind();
	void unbind();

	void printProgramLog(GLuint ID);
	void printShaderLog(GLuint ID);
	
	bool loadProgram(std::string glvs, std::string glfs);
	void freeProgram();

	virtual ~I_ShaderProgram(void) = 0 { };
};

#endif
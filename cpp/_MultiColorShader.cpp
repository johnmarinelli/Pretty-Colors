#include "_MultiColorShader.h"
#include <gtc/type_ptr.hpp>

_MultiColorShader::_MultiColorShader(void)
{
	m_ProgramID = NULL;
	m_VertexLocation = NULL;
	m_MultiColorLocation = NULL;

	m_ModelViewLocation = NULL;
	m_ProjectionLocation = NULL;
}

bool _MultiColorShader::_loadProgram(std::string glvs, std::string glfs)
{
	m_ProgramID = glCreateProgram();

	GLuint vertexShader = loadShaderFromFile(glvs, GL_VERTEX_SHADER);
	if(vertexShader == 0)
	{
		glDeleteProgram(m_ProgramID);
		printf("multicolor: Error loading %s\n", glvs);
		return false;
	}

	glAttachShader(m_ProgramID, vertexShader);

	GLuint fragmentShader = loadShaderFromFile(glfs, GL_FRAGMENT_SHADER);
	if(fragmentShader == 0)
	{
		glDeleteProgram(m_ProgramID);
		printf("multicolor: Error loading %s\n", glfs);
		return false;
	}

	glAttachShader(m_ProgramID, fragmentShader);

	glLinkProgram(m_ProgramID);

	GLint success = GL_TRUE;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
	if(success != GL_TRUE)
	{
		printf("Error linking program %d\n", m_ProgramID);
		printProgramLog(m_ProgramID);
		glDeleteProgram(m_ProgramID);
		m_ProgramID = NULL;
		return false;
	}

	//get variable locations
	m_VertexLocation = glGetAttribLocation(m_ProgramID, "in_vertexPosition");
	if(m_VertexLocation == -1)
	{
		printf("%s not a valid glsl program variable!", "in_vertexPosition");
		return false;
	}

	m_MultiColorLocation = glGetAttribLocation(m_ProgramID, "in_multiColor");
	if(m_MultiColorLocation == -1)
	{
		printf("%s not a valid glsl program variable!", "in_multiColor");
		return false;
	}

	//get uniform locations
	m_ProjectionLocation = glGetUniformLocation(m_ProgramID, "ProjectionMatrix");
	if(m_ProjectionLocation == -1)
	{
		printf("%s not valid glsl program variable", "ProjectionMatrix");
		return false;
	}

	m_ModelViewLocation = glGetUniformLocation(m_ProgramID, "ModelViewMatrix");
	if(m_ModelViewLocation == -1)
	{
		printf("%s not valid glsl program variable", "ModelViewMatrix");
		return false;
	}

	return true;
}

void _MultiColorShader::setModelView(glm::mat4 matrix)
{
	m_ModelViewMatrix = matrix;
}

void _MultiColorShader::setProjection(glm::mat4 matrix)
{
	m_ProjectionMatrix = matrix;
}

void _MultiColorShader::setVertexPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(m_VertexLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void _MultiColorShader::setColorPointer(GLsizei stride, const GLvoid* data)
{
	glVertexAttribPointer(m_MultiColorLocation, 4, GL_FLOAT, GL_FALSE, stride, data);
}

void _MultiColorShader::enablePointers()
{
	glEnableVertexAttribArray(m_VertexLocation);
	glEnableVertexAttribArray(m_MultiColorLocation);
}

void _MultiColorShader::disablePointers()
{
	glDisableVertexAttribArray(m_VertexLocation);
	glDisableVertexAttribArray(m_MultiColorLocation);
}

void _MultiColorShader::leftMultModelView(glm::mat4 matrix)
{
	m_ModelViewMatrix = matrix * m_ModelViewMatrix;
}

void _MultiColorShader::leftMultProjection(glm::mat4 matrix)
{
	m_ProjectionMatrix = matrix * m_ProjectionMatrix;
}

void _MultiColorShader::updateModelView()
{
	glUniformMatrix4fv(m_ModelViewLocation, 1, GL_FALSE, glm::value_ptr(m_ModelViewMatrix));
}

void _MultiColorShader::updateProjection()
{
	glUniformMatrix4fv(m_ProjectionLocation, 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix));
}

_MultiColorShader::~_MultiColorShader(void)
{
}

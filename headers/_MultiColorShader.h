#ifndef _MULTICOLORSHADER_H
#define _MULTICOLORSHADER_H

#include "I_shaderprogram.h"
#include <glm.hpp>

class _MultiColorShader :
	public I_ShaderProgram
{
private:
	GLint m_VertexLocation;
	GLint m_MultiColorLocation;

	glm::mat4 m_ModelViewMatrix;
	GLint m_ModelViewLocation;
	glm::mat4 m_ProjectionMatrix;
	GLint m_ProjectionLocation;

protected:
	bool _loadProgram(std::string glvs, std::string glfs);

public:
	_MultiColorShader();

	void setModelView(glm::mat4 matrix);
	void updateModelView();
	void setProjection(glm::mat4 matrix);
	void updateProjection();

	void leftMultModelView(glm::mat4 matrix);
	void leftMultProjection(glm::mat4 matrix);

	void setVertexPointer(GLsizei stride, const GLvoid* data);
	void setColorPointer(GLsizei stride, const GLvoid* data);

	void enablePointers();
	void disablePointers();

	void enableVertexPointer();

	~_MultiColorShader();
};

#endif
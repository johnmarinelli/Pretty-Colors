#include "_OpenGL.h"

#ifndef _VERTEX_POS_2D_H
#define _VERTEX_POS_2D_H


struct _Vertex2D
{
    GLfloat x;
    GLfloat y;
	
	_Vertex2D()
		: x(0.f), y(0.f)
	{
	}

	_Vertex2D(GLfloat _x, GLfloat _y)
		: x(_x), y(_y)
	{
	}
};

#endif


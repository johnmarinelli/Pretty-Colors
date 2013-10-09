#ifndef _MULTICOLORVERTEX2D_H
#define _MULTICOLORVERTEX2D_H

#include "_ColorRGBA.h"
#include "_Vertex2D.h"

struct _MultiColorVertex2D
	: public _Vertex2D
{
	_ColorRGBA rgba;

	_MultiColorVertex2D()
		: rgba(), _Vertex2D()
	{
	}

	_MultiColorVertex2D(GLfloat xPos, GLfloat yPos, GLfloat _r = 0.f, GLfloat _b = 0.f, GLfloat _g = 0.f, GLfloat _a = 1.f)
		: rgba(_r, _g, _b, _a), _Vertex2D(xPos, yPos) 
	{
	}
};

#endif
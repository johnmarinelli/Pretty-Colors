#include "_OpenGL.h"

#ifndef _COLORRGBA_H
#define _COLORRGBA_H

struct _ColorRGBA
{
private:
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;

public:
	_ColorRGBA(GLfloat _r = 0.f, GLfloat _b = 0.f, GLfloat _g = 0.f, GLfloat _a = 1.f)
		: r(_r), g(_g), b(_b), a(_a)
	{
	}

	void setColors(GLfloat _r, GLfloat _b, GLfloat _g, GLfloat _a = 1.f)
	{
		r = _r;
		b = _b;
		g = _g;
		a = _a;
	}

	void setColors(void (*__fptr)(GLfloat& r, GLfloat& g, GLfloat& b, GLfloat& a))
	{
		__fptr(r, g, b, a);
	}
};

#endif
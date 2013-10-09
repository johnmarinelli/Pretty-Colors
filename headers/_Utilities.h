#ifndef _UTILITES_H
#define _UTILITIES_H

#include "_OpenGL.h"
#include "_MessageCarrier.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 5;
const int TIME = 1000 / SCREEN_FPS;

const int MS_UNTIL_DEFAULT_OSCILLATE = 2500;

extern _MessageCarrier msgs;

bool initGL();
bool initGFXPrograms();
bool loadMedia();

void updateColorVBO();

/*THROW ALL OF THESE INTO 1 FXN*/
inline void oscillateColors(GLfloat& _r, GLfloat& _g, GLfloat& _b, GLfloat& _a);
inline void angryColors(GLfloat& _r, GLfloat& _g, GLfloat& _b, GLfloat& _a);
inline void sadColors(GLfloat& _r, GLfloat& _g, GLfloat& _b, GLfloat& _a);
inline void happyColors(GLfloat& _r, GLfloat& _g, GLfloat& _b, GLfloat& _a);

void updateColors(GLfloat& _r, GLfloat& _g, GLfloat& _b, GLfloat& _a);

void handleKeys(unsigned char key, int x, int y);
void update();
void render();

#endif


#include "_Utilities.h"
#include "Ftr_MoodState.h"

#include <iostream>

void initGLUT(const int &argc, char** args);
void runMainLoop(int val);

void (*vfp_handleKeys)(unsigned char, int, int);
void (*vfp_render)();
void (*vfp_mainLoop)(int);

Ftr_MoodState moodState;

int main(int argc, char* args[])
{
	//this is me being difficult
	initGLUT(const_cast<int&>(argc), args);

	if(!initGL()){
		printf("Unable to initialize GL : main\n");
		return 1;
	}

	if(!initGFXPrograms()){
		printf("Unable to initialize GFX Programs : main\n");
		return 2;
	}

	if(!loadMedia()){
		printf("Unable to load media : main\n");
		return 3;
	}

	//second thread
    moodState.start();
    moodState.addMessageCarrier(msgs);

	glutKeyboardFunc(vfp_handleKeys);
	glutDisplayFunc(vfp_render);
	glutTimerFunc(TIME, vfp_mainLoop, 0);

	glutMainLoop();
    
    return 0;
}

void initGLUT(const int &argc, char** args)
{
	glutInit(const_cast<int*>(&argc), args);
	glutInitContextVersion(3, 1);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Pretty Colors");
	
	vfp_handleKeys = &handleKeys;
	vfp_render = &render;
	vfp_mainLoop = &runMainLoop;
}

void runMainLoop(int val)
{
	update();
	render();
	
	glutTimerFunc(TIME, vfp_mainLoop, val);
}
#include "_Utilities.h"
#include "_MultiColorShader.h"
#include "_MultiColorVertex2D.h"
#include "UserMood.h"
#include "_Timer.h"
#include <gtx/transform.hpp>

const int VERTICES = 4;
const GLfloat dColor = .1f;

/*variables to control default oscillation*/
GLfloat amtChanged;
bool switchFader;

/*shader program and its variables*/
_MultiColorShader mcs;

GLuint vertex_vbo = NULL;
GLuint color_vbo = NULL;
GLuint ibo = NULL;
GLuint vao = NULL;

_ColorRGBA quadColors[VERTICES];

/*user input and a messaging system (msgs declared extern for main.cpp to use)*/
UserMood currentmood;
_MessageCarrier msgs;
_Timer timer;

//DEVIL NOT ENABLED
bool initGL()
{
	//initialize GLEW
	GLenum glewError = glewInit();
	if(glewError != GLEW_OK)
	{
		printf("Error initializing glew in initGL(): %s\n", glewGetErrorString(glewError));
		return false;
	}

	if(!GLEW_VERSION_2_1)
    {
        printf("OpenGL 2.1 not supported!\n");
        return false;
    }

	glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
        printf("Error initializing OpenGL! %s\n", gluErrorString(error));
        return false;
    }

	return true;
}

bool initGFXPrograms()
{
	if(!mcs.loadProgram("shaders/pc_vertexshader.glvs", "shaders/pc_fragmentshader.glfs")){
		printf("Couldn't load shader : initGFXPrograms\n");
		return false;
	}

	mcs.bind();
	
	mcs.setProjection(glm::ortho<GLfloat>(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0));
	mcs.updateProjection();
	mcs.setModelView(glm::mat4());
	mcs.updateModelView();

	return true;
}

bool loadMedia()
{
	amtChanged = 0.f;
	switchFader = false;

	_Vertex2D quadPos[4];
	GLuint indices[4];

	quadPos[0] = _Vertex2D(-(SCREEN_WIDTH / 2.f), -(SCREEN_HEIGHT / 2.f));
	quadPos[1] = _Vertex2D(SCREEN_WIDTH / 2.f, -(SCREEN_HEIGHT / 2.f));
	quadPos[2] = _Vertex2D(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
	quadPos[3] = _Vertex2D(-(SCREEN_WIDTH / 2.f), SCREEN_HEIGHT / 2.f);

	quadColors[0] = _ColorRGBA(1.f, 0.f, 0.f);
	quadColors[1] = _ColorRGBA(0.f, 1.f, 0.f);
	quadColors[2] = _ColorRGBA(0.f, 0.f, 1.f);
	quadColors[3] = _ColorRGBA(1.f, 1.f, 1.f);

	for(int i = 0; i < 4; ++i)
	{
		indices[i] = i;
	}

	glGenBuffers(1, &vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_Vertex2D) * 4, quadPos, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_ColorRGBA) * 4, quadColors, GL_DYNAMIC_DRAW);
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 4, indices, GL_DYNAMIC_DRAW);

	//vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	//enable pointers in our shading program
	mcs.enablePointers();

	//bind vertex vbo object to use
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	mcs.setVertexPointer(0, NULL);

	//bind color vbo object to use
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	mcs.setColorPointer(0, NULL);

	//bind ibo object to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	//unbind vao
	glBindVertexArray(NULL);

	mcs.disablePointers();

	return true;
}

void updateColorVBO()
{
	if(amtChanged > dColor * 10.f){
		switchFader = true;
	}

	else if(amtChanged < 0.f){
		switchFader = false;
	}

    for(int i = 0; i < VERTICES; ++i){
        quadColors[i].setColors(&updateColors);
    }

	//update color_vbo
	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_ColorRGBA) * 4, quadColors, GL_DYNAMIC_DRAW);
}

void updateColors(GLfloat& _r, GLfloat& _g, GLfloat& _b, GLfloat& _a)
{
    switch(currentmood)
    {
    case ANGRY: angryColors(_r, _g, _b, _a); break;
    case SAD: sadColors(_r, _g, _b, _a); break;
    case HAPPY: happyColors(_r, _g, _b, _a); break;
    default: oscillateColors(_r, _g, _b, _a); break;
    }
}

inline void oscillateColors(GLfloat& _r, GLfloat& _g, GLfloat& _b, GLfloat& _a)
{
	if(!switchFader){
		amtChanged += dColor;

		_r = _r > .99f ? .99f : _r + dColor;
		_g = _g > .99f ? .99f : _g + dColor;
		_b = _b > .99f ? .99f : _b + dColor;
	}

	else{
		amtChanged -= dColor;

		_r = _r < .01f ? .01f : _r - dColor;
		_g = _g < .01f ? .01f : _g - dColor;
		_b = _b < .01f ? .01f : _b - dColor;
	}
}

inline void angryColors(GLfloat& _r, GLfloat& _g, GLfloat& _b, GLfloat& _a)
{
    //increase red values
    _r = _r > .85f ? .85f : _r + dColor;
	_g = _g < .01f ? .01f : _g - dColor;
	_b = _b < .01f ? .01f : _b - dColor;
}

inline void sadColors(GLfloat& _r, GLfloat& _g, GLfloat& _b, GLfloat& _a)
{
    //increase g/b values
    _r = _r < .01f ? .01f : _r - dColor;
	_g = _g > .25f ? .25f : _g + dColor;
	_b = _b > .85f ? .85f : _b + dColor;
}

inline void happyColors(GLfloat& _r, GLfloat& _g, GLfloat& _b, GLfloat& _a)
{
    //increase g/r values
    _r = _r > .25f ? .25f : _r + dColor;
    _g = _g > .85f ? .85f : _g + dColor;
    _b = _b < .01f ? .01f : _b - dColor;
}

void handleKeys(unsigned char key, int x, int y)
{
}

void update()
{
    if(timer.isStopped()){
        timer.start();
    }

    currentmood = msgs.getMessage();

    if(timer.getTicks() > MS_UNTIL_DEFAULT_OSCILLATE){
           currentmood = DEFAULT;
           timer.stop();
           timer.reset();
    }

    //getstate
	updateColorVBO();

	//bind vao to use
	glBindVertexArray(vao);

	//enable pointers in our shading program
	mcs.enablePointers();

	//bind vertex vbo object to use
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	mcs.setVertexPointer(0, NULL);

	//bind color vbo object to use
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	mcs.setColorPointer(0, NULL);

	//bind ibo object to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	//unbind vao
	glBindVertexArray(NULL);

	mcs.disablePointers();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	mcs.setModelView(glm::translate<GLfloat>(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f));
	mcs.updateModelView();

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
	
	glutSwapBuffers();
}
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <stdbool.h>
#include <list>

//Include the different components
#include "Boat.h"
#include "Water.h"
#include "Vector2f.h"
#include "Cannon.h"
#include "Scene.h"
#include "Rigidbody2D.h"
#include "WaterCollider.h"
#include "IslandCannon.h"
#include "Renderer.h"
#include "RectangleCollider.h"
#include "Stats.h"
#include "Input.h"
#include "Planet.h"

#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

//METHOD DECLARATIONS
void drawHUD();

//CONSTANTS
const int milli = 1000;

//STRUCTS
struct Global {
	bool disableInput;
	bool waterTangent;
	bool waterNormal;
	bool debug;
	bool go;
	float startTime;
	bool OSD;
	int frames;
	float frameRate;
	float frameRateInterval;
	float lastFrameRateT;
	float dt;
};

//Scene object, has all gameobjects to be rendered / updated in it
Scene scene;

//GLOBAL VARIABLES
double lastT = 0;
long queuedMilliseconds;

// Stats to draw health bars
//I wanted to make a component that does this but ran out of time, would be neater to have everything in components

Global global = { false, false, false, true, false, 0.0, true, 0, 0.0, 0.2, 0.0 };

void update(void)
{
	double t, dt;
	t = glutGet(GLUT_ELAPSED_TIME) / (double)milli - (double)global.startTime;

	if (lastT < 0.0) {
		lastT = t;
		return;
	}

	//Calculates DeltaTime
	dt = t - lastT;

	if (dt == 0) {
		return;
	}
	global.dt = dt;
	lastT = t;

	//Calculates Frame Time
	dt = t - global.lastFrameRateT;
	if (dt > global.frameRateInterval) {
		global.frameRate = global.frames / dt;
		global.lastFrameRateT = t;
		global.frames = 0;
	}

	queuedMilliseconds += global.dt;
	while (queuedMilliseconds >= 10) {
		scene.fixedUpdate(global.dt, t);
		queuedMilliseconds -= 10;
	}

	//Updates game objects
	scene.update(global.dt, t);
	//Does post update work in scene
	scene.postUpdate();

	glutPostRedisplay();
}

void displayOSD()
{
	char buffer[30];
	char* bufp;
	int w, h;

	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	/* Set up orthographic coordinate system to match the
	   window, i.e. (0,0)-(w,h) */
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	/* Frame rate */
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos2i(10, 60);
	snprintf(buffer, sizeof buffer, "fr (f/s): %6.0f", global.frameRate);
	for (bufp = buffer; *bufp; bufp++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);

	/* Time per frame */
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos2i(10, 40);
	snprintf(buffer, sizeof buffer, "ft (ms/f): %5.0f", 1.0 / global.frameRate * 1000.0);
	for (bufp = buffer; *bufp; bufp++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);


	/* Pop modelview */
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);

	/* Pop projection */
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	/* Pop attributes */
	glPopAttrib();
}

void display(void)
{
	GLenum err;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Display Gameobjects
	scene.render();
	//Displays HUD
	drawHUD();

	// Display OSD
	if (global.OSD)
		displayOSD();

	glPopMatrix();

	glutSwapBuffers();

	global.frames++;

	// Check for errors
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("%s\n", gluErrorString(err));
}

void drawHUD() {

}

/*Initializes all the objects and components*/
void start()
{
	GameObject* planetOne = new GameObject("Planet One", &scene);
	Rigidbody2D* planetOneRb = new Rigidbody2D(planetOne, Vector3f(0, 0, 0), -0.5, 0);
	CircleCollider* planetOneColl = new CircleCollider(1, planetOne);
	Planet* planet = new Planet(planetOne);
	Renderer* planetOneRenderer = new Renderer(planetOne);
	planetOneRenderer->renderMode = Renderer::RenderMode::SPHERE;
	planetOne->transform.scale = Vector3f( 0.1, 0.1, 0.1 );
	planetOne->transform.position = Vector3f(0, 0.25, 0);
	planetOne->components.push_back(planet);
	planetOne->components.push_back(planetOneColl);
	planetOne->components.push_back(planetOneRb);
	planetOne->components.push_back(planetOneRenderer);
	
	
	GameObject* planetTwo = new GameObject("Planet Two", &scene);
	Rigidbody2D* planetTwoRb = new Rigidbody2D(planetTwo, Vector3f(0, 0, 0), 0, 0);
	CircleCollider* planetTwoColl = new CircleCollider(1, planetTwo);
	Renderer* planetTwoRenderer = new Renderer(planetTwo);
	planetTwoRenderer->renderMode = Renderer::RenderMode::SPHERE;
	planetTwo->transform.scale = Vector3f(0.1, 0.1, 0.1);
	planetTwo->transform.position = Vector3f(0, -0.25, 0);
	planetTwo->components.push_back(planetTwoColl);
	planetTwo->components.push_back(planetTwoRb);
	planetTwo->components.push_back(planetTwoRenderer);

	scene.instantiate(planetOne);
	scene.instantiate(planetTwo);
}

void keyboardCB(unsigned char key, int x, int y)
{
	//Updates which keys are pressed
	//Going to create an Input class for this that all components can interact with
	Input::pushKey(key);

	switch (key) {
	case 27:
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(500, 500);
	glutCreateWindow("Assignment One");
	glutKeyboardFunc(keyboardCB);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(update);

	//Enabled Transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	start();

	glutMainLoop();
}
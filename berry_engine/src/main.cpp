#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>


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

enum CoordSystem { cartesian, parametric, function, sine_wave, function_exp };
CoordSystem coordSystem = sine_wave;

enum RenderMode { points, lines };
RenderMode renderMode = lines;

struct Global { 
	float t;
	float lastT;
	float dt;
};

Global g;

bool debug = true;

int n = 32;

// Utility function for drawing axes
void drawAxes(float len)
{
#if 0
	glPushAttrib(GL_CURRENT_BIT);
#endif
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(len, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, len, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, len);
	glEnd();
#if 0
	glPopAttrib();
#endif
}

// Cartesian coordinates
void drawCircleCartesian(float r, int n)
{
	float x, y;

	if (debug)
		printf("drawCircleCartesian: %d\n", n);

	glColor3f(1.0, 1.0, 1.0);
	if (renderMode == points) {
		glPointSize(2.0);
		glBegin(GL_POINTS);
	}
	else {
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
	}

	n /= 2;

	for (int i = 0; i < n; i++) {
		x = ((i / (float)n - 0.5) * 2.0) * r;
		y = sqrt(r * r - x * x);
		if (debug)
			printf("x y: %f %f\n", x, y);
		glVertex2f(x, y);
		if (renderMode == points) {
			y = -y;
			if (debug)
				printf("x y: %f %f\n", x, y);
			glVertex2f(x, y);
		}
	}

	if (renderMode == lines)
		for (int i = n; i > 0; i--) {
			x = (i / (float)n - 0.5) * 2.0 * r;
			y = -sqrt(r * r - x * x);
			if (debug)
				printf("x y: %f %f\n", x, y);
			glVertex2f(x, y);
		}

	glEnd();

#if 0
	// Ignore
#endif
}

// Parametric coordinates
void drawCircleParametric(float r, int n)
{
	float x, y;
	float theta;

	if (debug)
		printf("drawCircleParametric: %d\n", n);

	glColor3f(1.0, 1.0, 1.0);
	if (renderMode == points) {
		glPointSize(2.0);
		glBegin(GL_POINTS);
	}
	else {
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
	}
	for (int i = 0; i < n; i++) {
		theta = i / (float)n * 2.0 * M_PI;
		x = r * cosf(theta);
		y = r * sinf(theta);
		if (debug)
			printf("x y: %f %f", x, y);
		glVertex2f(x, y);
	}
	glEnd();
}

void drawFunction(float n, float a, float b) {
	float x, y;
	float theta;

	if (debug)
		printf("drawCircleParametric: %f\n", n);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < n; i++) {
		theta = i / (float)n;

		x = theta;
		y = (a * theta) + b;

		if (debug)
			printf("x: %f, y: %f", x, y);

		glVertex2f(x, y);
	}
	glEnd();
}

void drawVector(float x, float y, float a, float b, float s, bool normalize) {
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_STRIP);

	glVertex2f(x, y);

	float newX = x + a;
	float newY = y + b;

	glVertex2f(newX, newY);

	glEnd();
}

void drawFunctionExp(float n, float a, float b, float c, float exp) {
	float x, y;
	float theta;

	if (debug)
		printf("\ndraw function exp: %f\n", n);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 1; i < n; i++) {
		theta = i / (float)n;

		x = theta;
		y = ((a * theta) * (a * theta)) + (b * x) + c;

		if (debug)
			printf("\nx: %f, y: %f", x, y);

		glVertex2f(x, y);
	}
	glEnd();
}

void drawSineWave(float n, float a) {
	float x, y;
	float theta;

	g.t = glutGet(GLUT_ELAPSED_TIME);
	g.dt = g.t - g.lastT;
	g.lastT = g.t;

	if (debug)
		printf("\ndraw function exp: %f\n", n);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 1; i < n; i++) {
		theta = i / (float)n;

		x = theta;
		float k = (2 * M_PI) / a;
		y = a * sinf(k * theta + g.dt);

		if (debug)
			printf("\nx: %f, y: %f dt: %f", x, y, g.dt);

		glVertex2f(x, y);
	}
	glEnd();
}

// Display callback
void display()
{
	int err;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawAxes(1.0);
	if (coordSystem == cartesian)
		drawCircleCartesian(1.0, n);
	else if (coordSystem == parametric)
		drawCircleParametric(1.0, n);
	else if (coordSystem == function)
		drawFunction(n, -0.5, 0);
	else if (coordSystem == sine_wave)
		drawSineWave(n, 0.5f);
	else if (coordSystem == function_exp)
		drawFunctionExp(n, 1, 0, 0, 2);

	// Always check for gl errors
	if ((err = glGetError()) != GL_NO_ERROR)
		fprintf(stderr, "Error: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

// Keyboard callback
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c':
		if (coordSystem == cartesian)
			coordSystem = parametric;
		else
			coordSystem = cartesian;
		break;
	case 'm':
		if (renderMode == lines)
			renderMode = points;
		else
			renderMode = lines;
		break;
	case 'd':
		debug = !debug;
		break;
	case '+':
		n *= 2;
		break;
	case '-':
		n /= 2;
		if (n < 2)
			n = 2;
		break;
	case 27:
		// ESCAPE key 
		exit(0);
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Circle");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}
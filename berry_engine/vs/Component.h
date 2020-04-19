#pragma once
#include <list>
#include "GameObject.h"

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

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/


//The base component class
//One gameobject can have multiple components
//Update gets called every frame
//Render gets called every render update
//beforeRender gets called ... before reder
//start gets called at the ... start
//On collision gets called when an objects collides with this object
class Component
{
public:
	virtual ~Component() { };
	Component() {
		gameObject = nullptr;
	}
	Component(GameObject* gameObject) {
		this->gameObject = gameObject;
	}
	GameObject* gameObject = nullptr;

	//Virtual Methods
	virtual void start() {};
	virtual void beforeRender() {};
	virtual void render() {};
	virtual void update(double deltaTime, double time) {};
	virtual void fixedUpdate(double deltaTime, double time) {};
	virtual void onCollision(GameObject* other) {};
};
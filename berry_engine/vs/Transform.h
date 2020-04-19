#pragma once
#include "Vector3f.h"
#include "Vector4f.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

//The transform object, contains position, rotation and scale
class Transform
{
public:
	//Constructors / Destructors
	~Transform() {};
	Transform() {
		scale = { 1,1,1 };
	}

	//Public Variables
	Vector3f position;
	Vector4f rotation;
	Vector3f scale;
};


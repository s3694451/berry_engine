#pragma once
#include "Component.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/


//Collider base class in which Circle Collider, Water collider and rectangle collider inherits from
class Collider : public Component
{
public:
	virtual bool collides(Collider* other) {
		return false;
	}
};


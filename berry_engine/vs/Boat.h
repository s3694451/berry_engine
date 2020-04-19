#pragma once
#include "Component.h"
#include "Water.h"
#include "Vector2f.h"
#include "Renderer.h"
#include "Input.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

class Boat : public Component
{
private:
	unsigned char moveLeft = 'a';
	unsigned char moveRight = 'd';
	Water* water = nullptr;
	double speed = 15;


public:
	int health = 10;
	//Constructors / Deconstructors
	~Boat() { };
	Boat() {
		moveLeft = 'a';
		moveLeft = 'd';
		water = nullptr;
	}

	Boat(GameObject* gameObject, unsigned char moveLeft, unsigned char moveRight, Water* water)
	{
		this->gameObject = gameObject;
		this->moveLeft = moveLeft;
		this->moveRight = moveRight;
		this->water = water;
	};

	//Methods
	void update(double deltaTime, double time) override {

		if (Input::hasKeyDown(moveRight)) {
			gameObject->transform.position.x += deltaTime * speed;
		}
		if (Input::hasKeyDown(moveLeft)) {
			gameObject->transform.position.x -= deltaTime * speed;
		}

		gameObject->transform.position.y = water->getY(gameObject->transform.position.x) - 1;

		Vector3f normal = water->getNormal(gameObject->transform.position);
		Vector2f polar = { normal.x, normal.y };
		polar = polar.toPolar();

		gameObject->transform.rotation.x = -polar.x * 45;
		gameObject->transform.rotation.w = 1;
	};

	void start() {

		//Gets the renderer on the object and sets up the points (trapezoid)
		Renderer* renderer = dynamic_cast<Renderer*> (gameObject->getComponent<Renderer>());
		renderer->points = { Vector3f(-0.5f,-0.25f, 0), Vector3f(0.5f,-0.25f, 0), Vector3f(1, 0.25, 0), Vector3f(-1, 0.25, 0) };
	}
};


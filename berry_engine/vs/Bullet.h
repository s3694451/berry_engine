#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Scene.h"
#include "Boat.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

class Bullet : public Component
{
private:
	float growRate = 0;
public:
	//Saves who shot the bullet so it cant hit himself
	GameObject* shooter;

	Bullet(GameObject* gameObject, GameObject* shooter) {
		this->gameObject = gameObject;
		this->shooter = shooter;
	};

	//How fast it grows, initially set to 0. used by island cannon to create pellet cloud
	void setGrowRate(float growRate) {
		this->growRate = growRate;
	}

	void update(double deltaTime, double time) override {
		if (growRate != 0) {
			gameObject->transform.scale = gameObject->transform.scale + (gameObject->transform.scale * growRate * deltaTime);
		}
		
	};

	//destroys the object if it collides with another bullet
	void onCollision(GameObject* other) {

		Bullet* bullet = dynamic_cast<Bullet*> (other->getComponent<Bullet>());

		if (bullet != nullptr) {
			other->scene->destroy(other);
		}
	}
};


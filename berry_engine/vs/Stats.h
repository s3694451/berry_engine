#pragma once
#include "Component.h"
#include "Bullet.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

//stats component displaying health, used for both boats and the island
class Stats : public Component
{
public:
	int health;
	int maxHealth;

	Stats(GameObject* gameObject, int health, int maxHealth) {
		this->gameObject = gameObject;
		this->health = health;
		this->maxHealth = maxHealth;
	}

	float getPercentage() {
		return ((float)health / (float)maxHealth);
	}

	//Collide with bullet -> reduce health
	void onCollision(GameObject* other) override {

		Bullet* bullet = dynamic_cast<Bullet*> (other->getComponent<Bullet>());

		if (bullet->shooter != gameObject) {
			if (health > 0) {
				health--;
			}
			other->scene->destroy(other);
		}

		
	}
};


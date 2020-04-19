#pragma once
#include "Collider.h"
#include "Water.h"
#include "CircleCollider.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

//Water Collider
class WaterCollider : public Collider
{
private:
	Water* water;
public:
	WaterCollider(Water* water, GameObject* gameObject) {
		this->gameObject = gameObject;
		this->water = water;
	}

	//only works with sphere collider right now
	bool collides(Collider* other) override {

		CircleCollider* otherCollider = dynamic_cast<CircleCollider*> (other);

		float yPos = water->getY(otherCollider->gameObject->transform.position.x);

		if (otherCollider != nullptr) {
			if (otherCollider->gameObject->transform.position.y <= (yPos - 1) + (otherCollider->getRadius() * 2)) {
				return true;
			}
		}

		return false;
	}

};
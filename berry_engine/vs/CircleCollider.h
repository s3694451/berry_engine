#pragma once
#include "Collider.h"
#include "Vector4f.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/


class CircleCollider : public Collider
{
private:
	float radius = 1;

public:
	
	float getRadius() {
		return radius * gameObject->transform.scale.x;
	}

	CircleCollider(float radius, GameObject* gameObject) {
		this->gameObject = gameObject;
		this->radius = radius;
	}

	bool collides(Collider* other) override {
		CircleCollider* otherCollider = dynamic_cast<CircleCollider*> (other);

		if (otherCollider != nullptr) {
			if (otherCollider->gameObject->transform.position.distance(&this->gameObject->transform.position) < otherCollider->getRadius() + getRadius()) {
				return true;
			}
		}

		return false;
	}
};


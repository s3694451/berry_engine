#pragma once
#include "Component.h"
#include "Rigidbody2D.h"
class Planet :
	public Component
{
public:
	Planet(GameObject* gameObject) : Component(gameObject){
	}
	void onCollision(GameObject* other) {
		Rigidbody2D* rb = dynamic_cast<Rigidbody2D*>(this->gameObject->scene->findObjectOfType<Rigidbody2D>());

		printf("\n vel: %f", rb->velocity.y);
		rb->velocity = Vector3f(0, 0.4f, 0);
	}
};


#pragma once
#include "Component.h"
#include "CircleCollider.h"
#include "Water.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

/* The base physics class used for bullets*/
class Rigidbody2D : public Component
{
private:
public:
	bool drawTrajectory = false;
	Vector3f velocity{ 0,0,0 };
	float gravity = -9.81f;
	float airResistance = 0.5f;


	Rigidbody2D(GameObject* gameObject, Vector3f velocity, float gravity, float airResistance) {
		this->velocity = velocity;
		this->gameObject = gameObject;
		this->gravity = gravity;
		this->airResistance = airResistance;
	}

	void render() override {

		if (!drawTrajectory)
			return;

		//Draws the trajectory of the physics object if drawTrajectory is enabled
		Water* waterComp = dynamic_cast<Water*>(gameObject->scene->findObjectOfType<Water>());
		Vector3f startPos(gameObject->transform.position.x, gameObject->transform.position.y, gameObject->transform.position.z);
		Vector2f vel(velocity.x, velocity.y);

		Vector2f pos(startPos.x, startPos.y);

		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		glVertex2f(pos.x, pos.y);

		float time = 5;

		int steps = 100;
		for (int i = 0; i < steps; i++) {
			float step = ((float)i / (float)steps) * (float)time;

			pos = pos + vel * step;

			vel.x = vel.x - vel.x * (airResistance * step);
			float distance = vel.y - (gravity + vel.y);
			vel.y = vel.y + distance * (gravity * step);

			if (waterComp != nullptr) {
				if (pos.y < waterComp->getY(pos.x) - 1) {
					glVertex2f(pos.x, waterComp->getY(pos.x) - 1);
					break;
				}
			}

			glVertex2f(pos.x, pos.y);
		}
		glEnd();
	}

	//Updates the position of the object using the airResistance and gravity variables
	void update(double deltaTime, double time) override {

		gameObject->transform.position = gameObject->transform.position + (velocity * deltaTime);

		velocity.x = velocity.x - velocity.x * (airResistance * deltaTime);
		float distance = velocity.y - (gravity + velocity.y);
		velocity.y = velocity.y + distance * (gravity * deltaTime);

		collisionDetection();
	};

	void collisionDetection() {
		//Collision Checking
		//Should be in its own FixedUpdate loop though
		std::list<GameObject*>::iterator it;
		for (it = gameObject->scene->gameobjects.begin(); it != gameObject->scene->gameobjects.end(); it++) {
			GameObject* gameObject = *it;

			if (gameObject == this->gameObject)
				continue;

			Collider* otherCollider = dynamic_cast<Collider*> (gameObject->getComponent<Collider>());
			Collider* thisCollider = dynamic_cast<Collider*> (this->gameObject->getComponent<Collider>());

			if (otherCollider != nullptr && thisCollider != nullptr) {
				if (otherCollider->collides(thisCollider) || thisCollider->collides(otherCollider)) {
					std::list<Component*>::iterator it;
					for (it = otherCollider->gameObject->components.begin(); it != otherCollider->gameObject->components.end(); it++) {
						(*it)->onCollision(thisCollider->gameObject);
					}
					for (it = thisCollider->gameObject->components.begin(); it != thisCollider->gameObject->components.end(); it++) {
						(*it)->onCollision(otherCollider->gameObject);
					}
				}
			}
		}
	}
};


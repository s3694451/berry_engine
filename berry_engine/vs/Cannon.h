#pragma once
#include "Component.h"
#include "Scene.h"
#include "GameObject.h"
#include "Rigidbody2D.h"
#include <math.h>
#include "Bullet.h"
#include "Renderer.h"
#include "Input.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

class Cannon : public Component
{
protected:
	unsigned char shoot = ' ';
	unsigned char left = ' ';
	unsigned char right = ' ';
	float zRotation = 0;
	float shootSpeed = 0;
	float rotationSpeed = 0;
	float cooldownTimer = 0;

public:
	float cooldown = 1;
	GameObject bullet;
	Boat* boat;

	Cannon(GameObject* gameObject, float rotationSpeed, float shootSpeed,  unsigned char shoot, unsigned char left, unsigned char right, Boat* boat) {
		this->shoot = shoot;
		this->rotationSpeed = rotationSpeed;
		this->gameObject = gameObject;
		this->left = left;
		this->right = right;
		this->shootSpeed = shootSpeed;
		this->boat = boat;
	}

	void update(double deltaTime, double time) override {

		//Updates cooldown, can only shoot if cooldown <= 0
		if (cooldownTimer > 0) {
			cooldownTimer -= deltaTime;
		}

		if (boat == nullptr || boat->health > 0) {
			if (Input::hasKeyDown(shoot) && cooldownTimer <= 0) {
				shootBullet();
				cooldownTimer = cooldown;
			}
			if (Input::hasKeyDown(left)) {
				zRotation += deltaTime * rotationSpeed;
			}
			if (Input::hasKeyDown(right)) {
				zRotation -= deltaTime * rotationSpeed;
			}
		}

		//Clamps the rotation
		if (zRotation > 90) {
			zRotation = 90;
		}
		if (zRotation < -90) {
			zRotation = -90;
		}

		//sets the Z rotation
		gameObject->transform.rotation.x = zRotation;
	};

	//Shoots the bullet
	virtual void shootBullet() {

		//Creates new gameobject
		GameObject* bullet = new GameObject("bullet", gameObject->scene);

		//calculates the total Z rot of this object + parent
		float totalZRot = gameObject->parent->transform.rotation.x + gameObject->transform.rotation.x;
		//calculates the direction based on the zRotation
		Vector2f dir = Vector2f(-totalZRot, 1).fromPolar();

		//Sets up the positon of the bullet
		Vector3f position = gameObject->parent->transform.position + gameObject->transform.position;
		//Moves it to the end of the cannon
		position = position + (dir * 0.15f);

		bullet->transform.position = position;
		bullet->transform.scale = { 0.025f, 0.025f, 0.025f };

		//Adds a physics component to the bullet
		Rigidbody2D* rb = new Rigidbody2D(bullet, Vector3f(dir.x, dir.y, 0) * shootSpeed, -0.5f, 0.05f);
		//Adds the component to the object
		bullet->components.push_back(rb);
		//Displays the trajectory
		rb->drawTrajectory = true;

		//Adds circle collider to the object
		CircleCollider* col = new CircleCollider(1, bullet);
		bullet->components.push_back(col);

		//Adds a bullet component to the object
		Bullet* blt = new Bullet(bullet, gameObject->parent);
		bullet->components.push_back(blt);

		//Adds a renderer to the bullet
		Renderer* renderer = new Renderer(bullet);
		renderer->renderMode = Renderer::RenderMode::SPHERE;
		bullet->components.push_back(renderer);

		//Adds bullet to the scene
		gameObject->scene->instantiate(bullet);
	}


	void start() override {
		//gets the gameobejct z rotation from start
		zRotation = gameObject->transform.rotation.x;
		Renderer* renderer = dynamic_cast<Renderer*> (gameObject->getComponent<Renderer>());
		//sets up graphics
		renderer->points = { Vector3f(-0.5,0, 0), Vector3f(-0.5,3, 0), Vector3f(0.5, 3, 0), Vector3f(0.5, 0, 0) };
	}

};


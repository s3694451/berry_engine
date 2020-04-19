#pragma once
#include "Cannon.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

class IslandCannon : public Cannon
{
private:
	//How fast the bullet grows
	float growRate = 0;
public:
	IslandCannon(float growRate,GameObject* gameObject, 
		float rotationSpeed, float shootSpeed, unsigned char shoot, 
		unsigned char left, unsigned char right, Boat* boat) :Cannon(gameObject, rotationSpeed, shootSpeed, shoot, left, right, boat) {
		this->growRate = growRate;
	}

	void fixedUpdate(double deltaTime, double time) override {
		printf("\n called");
	}

	//same as in "Cannon.h"
	//but adds the grow rate to the bullet
	void shootBullet() override {
		GameObject* bullet = new GameObject("bullet", gameObject->scene);

		float totalZRot = gameObject->parent->transform.rotation.x + gameObject->transform.rotation.x;
		Vector2f dir = Vector2f(-totalZRot, 1).fromPolar();

		Vector3f position = gameObject->parent->transform.position + gameObject->transform.position;
		position = position + (dir * 0.15f);

		bullet->transform.position = position;
		bullet->transform.scale = { 0.025f, 0.025f, 0.025f };

		Rigidbody2D* rb = new Rigidbody2D(bullet, Vector3f(dir.x, dir.y, 0) * shootSpeed, -0.5f, 0.05f);
		bullet->components.push_back(rb);
		rb->drawTrajectory = true;

		CircleCollider* col = new CircleCollider(1, bullet);
		bullet->components.push_back(col);

		Bullet* blt = new Bullet(bullet, gameObject->parent);
		blt->setGrowRate(growRate);
		blt->shooter = gameObject;
		bullet->components.push_back(blt);

		Renderer* renderer = new Renderer(bullet);
		renderer->renderMode = Renderer::RenderMode::WIRE_SPHERE;
		bullet->components.push_back(renderer);

		gameObject->scene->instantiate(bullet);
	}
};


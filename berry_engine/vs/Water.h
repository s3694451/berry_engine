#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Bullet.h"
#include "Input.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

//water component used to render the water. should really inherit from Renderer but oh well
class Water : public Component
{
private:
	float time = 0;
	float speed = 0.1f;
	float amplitude = 0.05f;
	float density = 10;
	bool animate = true;
	bool showTangents = false;
	bool showNormal = false;
public:
	//Constructors / Destructors
	~Water() { };
	Water() {};
	Water(float speed,float amplitude,float density,GameObject* gameObject) {
		this->gameObject = gameObject;
		this->speed = speed;
		this->amplitude = amplitude;
		this->density = density;
	};

	//Methods
	void update(double deltaTime, double time) override {

		//Decrease density
		if (Input::hasKeyDown('-')) {
			density--;

			//Cap at 4
			if (density < 3) {
				density = 3;
			}
		}

		//Display normals
		if (Input::hasKeyDown('n')) {
			showNormal = !showNormal;
		}
		//display tangents
		if (Input::hasKeyDown('t')) {
			showTangents = !showTangents;
		}


		if (Input::hasKeyDown('+')) {
			density *= 2;
		}

		if (Input::hasKeyDown('g')) {
			animate = !animate;
		}

		if (animate) {
			this->time += deltaTime * speed;
		}
		
	};

	//Destroy bullet if it collides
	void onCollision(GameObject* other) override {
		Bullet* bullet = dynamic_cast<Bullet*> (other->getComponent<Bullet>());

		if (bullet != nullptr) {
			other->scene->destroy(other);
		}
		
	};

	void render() {
		//Displays the normals / tangents if show is on
		Renderer* rnd = dynamic_cast<Renderer*> ((gameObject->getComponent<Renderer>()));

		if (showNormal) {
			std::list<Vector3f>::iterator vIt;
			for (vIt = rnd->points.begin(); vIt != rnd->points.end(); vIt++) {
				Vector3f vector = *vIt;
				if (vector.y > 0) {
					Vector3f normal = getNormal(vector);
					vector.y -= 1;
					rnd->renderVector(vector, normal, 0.1f, Vector4f(1, 1, 1, 1));
				}
			}
		}
		if (showTangents) {
			std::list<Vector3f>::iterator vIt;
			for (vIt = rnd->points.begin(); vIt != rnd->points.end(); vIt++) {
				Vector3f vector = *vIt;
				if (vector.y > 0) {
					Vector3f tangent = getTangent(vector);
					vector.y -= 1;
					rnd->renderVector(vector, tangent, 0.1f, Vector4f(1, 0, 0, 1));
				}
			}
		}
	}

	void beforeRender() override {
		//base Points, Bottom left and bottom right
		std::list<Vector3f> _points = { Vector3f(-1,-1, 0) };

		//Sin to calculate Y for each X pos
		for (int i = 0; i <= density; i++) {
			float p = i / density;
			float x = -1 + (p * 2);
			float y = getY(x);
			_points.push_back(Vector3f(x, y, 0));
		}

		_points.push_back(Vector3f(1, -1, 0));
		Renderer* renderer = dynamic_cast<Renderer*> (gameObject->getComponent<Renderer>());

		if (renderer != nullptr) {
			//adds points to the renderer
			renderer->points = _points;
		}
		
	};

	//calculate the normal at position
	Vector3f getNormal(Vector3f position) {
		Vector3f normal;
		Vector3f firstPos = position;
		firstPos.x -= 0.1f;
		Vector3f secondPos = position;
		secondPos.x += 0.1f;

		firstPos.y = getY(firstPos.x);
		secondPos.y = getY(secondPos.x);

		Vector3f dir = secondPos - firstPos;
		normal = { -dir.y, dir.x, 0 };

		return normal;
	};

	//calculate the tangent at position 
	Vector3f getTangent(Vector3f position) {
		Vector3f firstPos = position;
		firstPos.x -= 0.1f;
		Vector3f secondPos = position;
		secondPos.x += 0.1f;
		firstPos.y = getY(firstPos.x);
		secondPos.y = getY(secondPos.x);
		Vector3f dir = secondPos - firstPos;
		return dir;
	};

	//gets the Y value of X
	//uses time and aplitude
	float getY(float x) {
		return sinf(x + time) * amplitude + 1;
	};
};
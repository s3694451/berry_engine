#pragma once
#include "Collider.h"
#include "CircleCollider.h"
/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/


class RectangleCollider : public Collider
{
private:
	//Size of the collider
	float xSize;
	float ySize;
public:

	RectangleCollider(GameObject* gameObject, float xSize, float ySize) {
		this->gameObject = gameObject;
		this->xSize = xSize;
		this->ySize = ySize;
	}

	float getXSize() {
		return xSize;
	}

	float getYSize() {
		return ySize;
	}

	virtual bool collides(Collider* other) {
		CircleCollider* circleCollider = dynamic_cast<CircleCollider*> (other);
		RectangleCollider* rectangleCollider = dynamic_cast<RectangleCollider*> (other);

		Vector3f truePos = gameObject->transform.position;
		if (gameObject->parent != nullptr) {
			truePos = gameObject->transform.position + gameObject->parent->transform.position;
		}

		//Could think of a fix for this, will work on it
		truePos.x -= 0.25f;
		truePos.y -= 1;
		
		Vector3f player1 = circleCollider->gameObject->transform.position;
		Vector3f player2 = truePos;

		if (circleCollider != nullptr) {
			if (player1.x < player2.x + xSize &&
				player1.x + circleCollider->getRadius() > player2.x &&
				player1.y < player2.y + ySize &&
				player1.y + circleCollider->getRadius() > player2.y)
			{
				return true;
			}
		
		}
		else if (rectangleCollider != nullptr) {
			if (player1.x < player2.x + xSize &&
				player1.x + circleCollider->getRadius() > player2.x &&
				player1.y < player2.y + ySize &&
				player1.y + circleCollider->getRadius() > player2.y)
			{
				return true;
			}
		}

		return false;
	}

};


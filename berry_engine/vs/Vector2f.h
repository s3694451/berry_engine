#pragma once
#include "Vector3f.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/


//A vector 2 object. can also be used for polar angles
class Vector2f : public Vector3f
{
public:
	~Vector2f() {};
	Vector2f() {
		x = 0;
		y = 0;
	}

	Vector2f(float x, float y) {
		this->x = x;
		this->y = y;
	}

	float magnitude() {
		return sqrt((x * x) + (y * y));
	}

	//X = Angle;
	//Y = Magnitude;
	Vector2f toPolar() {
		Vector2f polar;
		polar.x = atan(x / y);
		polar.y = magnitude();
		return polar;
	}

	Vector2f fromPolar() {
		float radians = x * ((3.14f * (float)2) / (float)360);
		Vector2f vector;
		vector.x = sinf(radians);
		vector.y = cosf(radians);
		return vector;
	}

	Vector4f normalized() {
		Vector2f vector(x, y);
		vector = vector / magnitude();
		return vector;
	}

	Vector2f operator*(const float m) {
		Vector2f vector;
		vector.x = this->x * m;
		vector.y = this->y * m;
		return vector;
	}

	Vector2f operator+(const Vector2f v) {
		Vector2f vector;
		vector.x = this->x + v.x;
		vector.y = this->y + v.y;
		return vector;
	}

	Vector2f operator-(const Vector2f v) {
		Vector2f vector;
		vector.x = this->x - v.x;
		vector.y = this->y - v.y;
		return vector;
	}

	Vector2f operator*(const Vector2f v) {
		Vector2f vector;
		vector.x = this->x * v.x;
		vector.y = this->y * v.y;
		return vector;
	}

	Vector2f operator/(const Vector2f v) {
		Vector2f vector;
		vector.x = this->x / v.x;
		vector.y = this->y / v.y;
		return vector;
	}

	Vector2f operator/(const float f) {
		Vector2f vector;
		vector.x = this->x / f;
		vector.y = this->y / f;
		return vector;
	}
};
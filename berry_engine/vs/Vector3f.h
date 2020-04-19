#pragma once
#include "Vector4f.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

//Vector 3 object
class Vector3f : public Vector4f
{
public:
	~Vector3f() {};
	Vector3f() {
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3f(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3f operator+(const Vector3f v) {
		Vector3f vector;
		vector.x = this->x + v.x;
		vector.y = this->y + v.y;
		vector.z = this->z + v.z;
		return vector;
	}

	float magnitude() {
		return sqrt((x * x) + (y * y) + (z * z));
	}

	Vector4f normalized() {
		Vector3f vector(x, y, z);
		vector = vector / magnitude();
		return vector;
	}


	Vector3f operator*(const float m) {
		Vector3f vector;
		vector.x = this->x * m;
		vector.y = this->y * m;
		vector.z = this->z * m;
		return vector;
	}

	Vector3f operator-(const Vector3f v) {
		Vector3f vector;
		vector.x = this->x - v.x;
		vector.y = this->y - v.y;
		vector.z = this->z - v.z;
		return vector;
	}

	Vector3f operator*(const Vector3f v) {
		Vector3f vector;
		vector.x = this->x * v.x;
		vector.y = this->y * v.y;
		vector.z = this->z * v.z;
		return vector;
	}

	Vector3f operator/(const Vector3f v) {
		Vector3f vector;
		vector.x = this->x / v.x;
		vector.y = this->y / v.y;
		vector.z = this->z / v.z;
		return vector;
	}

	Vector3f operator/(const float f) {
		Vector3f vector;
		vector.x = this->x / f;
		vector.y = this->y / f;
		vector.z = this->z / f;
		return vector;
	}

};
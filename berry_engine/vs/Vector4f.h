#pragma once
#include <math.h>

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/

//The base vector class
//Has operator overloads, Magnitude calculation and normalization calucation
class Vector4f
{
public:
	~Vector4f() {};
	float x;
	float y;
	float z;
	float w;

	Vector4f() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	Vector4f(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	virtual float magnitude() {
		return sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	float distance(Vector4f* other) {
		Vector4f from{ x,y,z,w };
		Vector4f to{ other->x,other->y,other->z,other->w };
		to = from - to;
		return to.magnitude();
	}

	virtual Vector4f normalized() {
		Vector4f vector(x,y,z,w);
		vector = vector / magnitude();
		return vector;
	}

	Vector4f operator+(const Vector4f v) {
		Vector4f vector;
		vector.x = this->x + v.x;
		vector.y = this->y + v.y;
		vector.z = this->z + v.z;
		vector.w = this->w + v.w;
		return vector;
	}

	Vector4f operator-(const Vector4f v) {
		Vector4f vector;
		vector.x = this->x - v.x;
		vector.y = this->y - v.y;
		vector.z = this->z - v.z;
		vector.w = this->w - v.w;
		return vector;
	}

	Vector4f operator*(const Vector4f v) {
		Vector4f vector;
		vector.x = this->x * v.x;
		vector.y = this->y * v.y;
		vector.z = this->z * v.z;
		vector.w = this->w * v.w;
		return vector;
	}

	Vector4f operator*(const float m) {
		Vector4f vector;
		vector.x = this->x * m;
		vector.y = this->y * m;
		vector.z = this->z * m;
		vector.w = this->w * m;
		return vector;
	}

	Vector4f operator/(const Vector4f v) {
		Vector4f vector;
		vector.x = this->x / v.x;
		vector.y = this->y / v.y;
		vector.z = this->z / v.z;
		vector.w = this->w / v.w;
		return vector;
	}

	Vector4f operator/(const float f) {
		Vector4f vector;
		vector.x = this->x / f;
		vector.y = this->y / f;
		vector.z = this->z / f;
		vector.w = this->w / f;
		return vector;
	}

};


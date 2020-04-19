#pragma once
#include "Component.h"
#include "Vector2f.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/


/* THE BASE RENDERER
Has multiple ways to render including rendering a vector */
class Renderer : public Component
{
public:
	//Public Variables
	enum RenderMode {
		POINTS,
		SPHERE,
		WIRE_SPHERE,
	};
	std::list<Vector3f> points;
	RenderMode renderMode = Renderer::RenderMode::POINTS;
	Vector4f color{ 1,1,1,1 };

	Renderer(GameObject* gameObject) {
		this->gameObject = gameObject;
	}

	void renderVector(Vector3f origin, Vector3f vector, float magnitude, Vector4f color)
	{
		glPushMatrix();
		glColor4f(color.x, color.y, color.z, color.w);
		glBegin(GL_LINE_STRIP);

		glVertex2f(origin.x, origin.y);
		vector = vector / vector.magnitude();
		Vector3f endVector = origin + (vector * magnitude);
		glVertex2f(endVector.x, endVector.y);

		glEnd();
		glPopMatrix();
	}

	void render() override {
		Transform transform = gameObject->transform;
		std::list<Vector3f> points = this->points;
		Vector4f color = this->color;

		Vector3f scale = gameObject->transform.scale;
		Vector3f position = gameObject->transform.position;
		Vector4f rotation = gameObject->transform.rotation;

		if (gameObject->parent != nullptr) {
			scale = gameObject->transform.scale * gameObject->parent->transform.scale;
			position = gameObject->transform.position + gameObject->parent->transform.position;
			if (gameObject->parent->transform.rotation.w == 1 || rotation.w == 1) {
				rotation.w = 1;
			}

			rotation.x += gameObject->parent->transform.rotation.x;
		}

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale.x, scale.y, scale.z);
		glRotatef(rotation.x, rotation.y, rotation.z, rotation.w);

		glColor4f(color.x, color.y, color.z, color.w);

		if (renderMode == Renderer::RenderMode::POINTS) {
			glBegin(GL_POLYGON);
			std::list<Vector3f>::iterator pointIt;

			for (pointIt = points.begin(); pointIt != points.end(); pointIt++) {
				Vector2f point = Vector2f(pointIt->x, pointIt->y);
				glVertex2d(point.x, point.y);
			}
			glEnd();
		}
		else if (renderMode == Renderer::RenderMode::SPHERE) {
			glutSolidSphere(1, 16, 16);
		}
		else if (renderMode == Renderer::RenderMode::WIRE_SPHERE) {
			glutWireSphere(1, 16, 16);
		}

		glPopMatrix();
	}
};


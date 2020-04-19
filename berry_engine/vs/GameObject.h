#pragma once
#include <iterator>
#include "Transform.h"
#include <list>

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/


//Forward declarations
class Scene;
class Component;

class GameObject
{
public:

	//The scene of the object
	Scene* scene = nullptr;
	//Name of the object
	std::string name = "object";
	//transform of the object
	//Position, rotation and scale
	Transform transform;

	//The list of components on the object
	std::list<Component*> components;
	//The gameobjects children
	std::list<GameObject*> children;

	//the parent of this object
	GameObject* parent = nullptr;
	//Was going to move this to a static class but ran out of time, stores all the keys that are pressed down

	//Constructors
	~GameObject() {};
	GameObject() {}
	GameObject(std::string name, Scene* scene) {
		this->name = name;
		this->scene = scene;
		parent = nullptr;
	}

	//Gets a component of type T on this object, if it doesnt have one -> return null ptr
	template<class T>
	Component* getComponent()
	{
		std::list<Component*>::iterator it;
		for (it = components.begin(); it != components.end(); it++) {
			Component* component = *it;
			if (dynamic_cast<T*>(component) != nullptr)
			{
				return component;
			}
		}
		return nullptr;
	}

	//Public Methods
	//sets the parent of this object. also adds the object to the parents children list
	void setParent(GameObject* other) {
		other->children.push_back(this);
		parent = other;
	};
};
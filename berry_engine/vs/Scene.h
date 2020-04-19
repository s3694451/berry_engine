#pragma once
#include "GameObject.h"
#include <list>
#include "Input.h"

/*
	Simon Hesjevik
	Student ID: s3694451
	COSC 1186/1187: Interactive 3D Graphics and Animation
	Semester 1 2020
	RMIT University, Melbourne
*/


/*The scene object where all gameobjects are stored in*/
class Scene
{
public:
	//list of all game object
	std::list<GameObject*> gameobjects;

	//Store of gameobjects to destroy after each update loop not to break the iteration
	std::list<GameObject*> gameobjectsToDestroy;

	//Adds the object to the list
	void instantiate(GameObject* gameObject) {
		gameobjects.push_back(gameObject);
		
		std::list<Component*>::iterator compIt;
		for (compIt = gameObject->components.begin(); compIt != gameObject->components.end(); compIt++) {
			(*compIt)->start();
		}
	};

	//Finds an object with component T
	template<class T>
	Component* findObjectOfType()
	{
		std::list<GameObject*>::iterator it;
		for (it = gameobjects.begin(); it != gameobjects.end(); it++) {
			GameObject* gameObject = *it;
			
			Component* comp = gameObject->getComponent<T>();
			
			if (dynamic_cast<T*>(comp) != nullptr)
			{
				return comp;
			}
		}
		return nullptr;
	}

	void update(double deltaTime, double time) {
		std::list<GameObject*>::iterator it;
		for (it = gameobjects.begin(); it != gameobjects.end(); it++) {
			GameObject* go = *it;
			std::list<Component*>::iterator compIt;
			for (compIt = go->components.begin(); compIt != go->components.end(); compIt++) {
				(*compIt)->update(deltaTime, time);
			}

			//Updates which keys are down
		}
	}

	void fixedUpdate(double deltaTime, double time) {

		printf("\n calling fixed");
		std::list<GameObject*>::iterator it;
		for (it = gameobjects.begin(); it != gameobjects.end(); it++) {
			GameObject* go = *it;
			std::list<Component*>::iterator compIt;
			for (compIt = go->components.begin(); compIt != go->components.end(); compIt++) {
				(*compIt)->fixedUpdate(deltaTime, time);
			}

			//Updates which keys are down
		}
	}

	void render() {
		std::list<GameObject*>::iterator it;
		for (it = gameobjects.begin(); it != gameobjects.end(); it++) {
			GameObject* gameObject = *it;
			std::list<Component*>::iterator compIt;
			for (compIt = gameObject->components.begin(); compIt != gameObject->components.end(); compIt++) {
				(*compIt)->beforeRender();
				(*compIt)->render();
			}

		}
	}

	//Adds an object to the list to be removed
	void destroy(GameObject* gameObject) {
		gameobjectsToDestroy.push_back(gameObject);
	}

	//removes the objects from the main list
	void postUpdate() {
		std::list<GameObject*>::iterator it;
		for (it = gameobjectsToDestroy.begin(); it != gameobjectsToDestroy.end(); it++) {
			GameObject* gameObject = *it;

			gameobjects.remove(gameObject);
		}

		Input::clearKeys();
	}
};
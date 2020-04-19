#pragma once
#include <list>
#include <algorithm>

class Input
{
private:
	
public:
	static std::list<unsigned char> keysDown;
	static std::list<unsigned char> getKeysDown() {
		return keysDown;
	}

	static void pushKey(unsigned char key) {
		keysDown.push_back(key);
	}

	static void clearKeys() {
		keysDown.clear();
	}
	static bool hasKeyDown(unsigned char key) {
		return (std::find(Input::keysDown.begin(), Input::keysDown.end(), key) != Input::keysDown.end());
	};
};

std::list<unsigned char> Input::keysDown =  {};
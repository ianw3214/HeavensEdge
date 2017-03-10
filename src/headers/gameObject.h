#pragma once

#include <SDL.h>

/**
* Abstract class providing base functions shared across game objects
*/
class GameObject {

public:
	GameObject();

	void setType(int);
	int getType();
	bool shouldRemove();

	virtual ~GameObject() {};
	virtual void render(SDL_Surface*, SDL_Rect) = 0;
	virtual void update(float) = 0;
protected:
	// TYPE is represented by ints for now, eventually want to move to ENUMS
	//		- 0 stands for generic types
	//		- 1 stands for hero type
	//		- 2 stands for enemy types
	int TYPE;
	bool REMOVE;
};

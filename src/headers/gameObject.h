#pragma once

#include <SDL.h>

/**
* Abstract class providing base functions shared across game objects
*/
class GameObject {

public:
	virtual ~GameObject() {};
	virtual void render(SDL_Surface*, SDL_Rect) = 0;
	virtual void update(float) = 0;
};

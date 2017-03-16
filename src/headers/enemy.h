#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "entity.h"

/**
 * Base enemy class representing any enemy creature
 */
class Enemy : public Entity {

public:

	Enemy();
	Enemy(int, int);
	virtual ~Enemy() {};

	void update(float);
	void render(SDL_Surface*, SDL_Rect);
private:
	void init();
};
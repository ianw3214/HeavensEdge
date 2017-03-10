#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "entity.h"
#include "animatedSprite.h"

class Enemy : public Entity {

public:

	Enemy();
	Enemy(int, int);
	virtual ~Enemy() {};

	void update(float);
	void render(SDL_Surface*, SDL_Rect);
private:
	int x, y;

	AnimatedSprite * sprite;

	void init();
};
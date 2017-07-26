#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "creature.h"
#include "collision.h"
#include "constants.h"

#include <iostream>

/**
 * Base enemy class representing any enemy creature
 */
class Enemy : public Creature {

public:

	Enemy();
	Enemy(int, int);
	virtual ~Enemy() {};

	void update(float);
	void render(SDL_Surface*, SDL_Rect);
private:
	void init();

	// movement related variables/functions
	void move(float);
	int currentDir;	// 0 - Up, 1 - Right, 2 - Down, 3 - Left
	float idleTimer;

	int speed;
};
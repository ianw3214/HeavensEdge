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
	void render(SDL_Renderer*, SDL_Rect);
private:
	// enumeration to represent the different animation states of the sprite
	enum ANIM_STATE {
		IDLE_DOWN = 0,
		IDLE_RIGHT = 1,
		IDLE_UP = 2,
		IDLE_LEFT = 3,
		RUN_DOWN = 4,
		RUN_RIGHT = 5,
		RUN_UP = 6,
		RUN_LEFT = 7
	};
	int animState;

	void init();

	// movement related variables/functions
	void move(float);
	int currentDir;	// 0 - Up, 1 - Right, 2 - Down, 3 - Left
	float idleTimer;
};
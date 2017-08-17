#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "enemy.h"
#include "hero.h"
#include "player.h"

#include "constants.h"
#include "collision.h"

#include <iostream>

class ChargeEnemy : public Enemy { 

public:

	ChargeEnemy();
	ChargeEnemy(int, int);
	virtual ~ChargeEnemy() {};

	void update(float);
	void render(SDL_Renderer*, SDL_Rect);
private:
	// enumeration to represent the different animation states of the sprite
	enum ANIM_STATE {
		IDLE_DOWN = 0,
		IDLE_RIGHT = 1,
		IDLE_UP = 2,
		IDLE_LEFT = 3,
		CHARGE_DOWN = 4,
		CHARGE_RIGHT = 5,
		CHARGE_UP = 6,
		CHARGE_LEFT = 7
	};
	int animState;

	void init(int, int);

	bool charging;
	int direction;
	float chargeTimer;

	Hero * hero;
};
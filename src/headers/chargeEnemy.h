#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "enemy.h"
#include "hero.h"
#include "player.h"

#include "collision.h"

#include <iostream>

class ChargeEnemy : public Enemy {

public:

	ChargeEnemy();
	ChargeEnemy(int, int);
	virtual ~ChargeEnemy() {};

	void update(float);
	void render(SDL_Surface*, SDL_Rect);
private:
	void init(int, int);

	bool charging;
	int direction;
	float chargeTimer;
	float CHARGEBAR = 1.5f;

	Hero * hero;

	int const CHARGESPEED = 400;
};
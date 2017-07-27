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
	void init(int, int);

	bool charging;
	int direction;
	float chargeTimer;

	Hero * hero;
};
#pragma once

#include <SDL.h>

#include "entity.h"
#include "animatedSprite.h"

class Creature : public Entity{
public:
	Creature();
	Creature(int, int);
	Creature(int, int, int);

	void takeDamage(int);
	int getHealth() const;

	void handleEvents(SDL_Event);
	void update(float);
	void render(SDL_Surface*, SDL_Rect);
	
protected:
	int health;

	int x, y;

	AnimatedSprite * sprite;

	void init(int, int, int);
};
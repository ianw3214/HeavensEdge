#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>

#include "creature.h"
#include "collision.h"

#include "constants.h"

/**
 * Base hero class representing entities controllable by the player
 */
class Hero : public Creature{

public:
    Hero(int, int);
	virtual ~Hero() {};

	// getter/setter functions
	void setLevelWidth(int);
	void setPos(int, int);
	void setEntities(std::vector<Entity*>*);
	int getX() const;
	int getY() const;

    virtual void update(float);
    virtual void render(SDL_Surface*, SDL_Rect);

	virtual void key1Attack(int);
	virtual void key2Attack(int);

	// methods to interact with animated sprite from outside
	void playAnimation(int);
	void setNextAnimation(int);
	void resetAnimationFrame();

	void move(int, float);
protected:
	int dashDirection;
	bool dashing;
	float dashTimer;

	std::vector<Entity*>* entityList;

	std::vector<AnimatedSprite*> effects;

};

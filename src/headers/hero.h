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
	void setPos(int, int);
	void setEntities(std::vector<Entity*>*);
	int getX() const;
	int getY() const;
	void syncMoveKeys(bool*, bool*, bool*, bool*);

    virtual void update(float);
    virtual void render(SDL_Surface*, SDL_Rect);

	virtual void key1Attack();
	virtual void key2Attack();

	// methods to interact with animated sprite from outside
	void playAnimation(int);
	void setNextAnimation(int);
	void resetAnimationFrame();

protected:
	int animState;
	bool faceRight;
	bool *upPress, *rightPress, *downPress, *leftPress;

	int dashDirection;
	bool dashing, attacking;
	float dashTimer, attackTimer;

	std::vector<Entity*>* entityList;

	std::vector<AnimatedSprite*> effects;

private:
	enum ANIM_STATE {
		IDLE_RIGHT = 0,
		IDLE_LEFT = 1,
		MOVE_RIGHT = 2,
		MOVE_LEFT = 3,
		ATTACK1RIGHT = 4,
		ATTACK1LEFT = 5,
		DASH_RIGHT = 6,
		DASH_LEFT = 7,
		COMBO1_RIGHT = 8,
		COMBO1_LEFT = 9
	};

	void move(float);

	// handle all combo attacks in each specific class, so it is private
	void combo1Attack();
};

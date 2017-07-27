#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>
#include <cmath>

#include "creature.h"
#include "collision.h"
#include "npc.h"

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
	int getX() const;
	int getY() const;
	void syncMoveKeys(bool*, bool*, bool*, bool*);

	void takeDamage(int);

    virtual void update(float);
    virtual void render(SDL_Renderer*, SDL_Rect);

	virtual void key1Attack();
	virtual void key2Attack();

	virtual void handleDialogue();

	// methods to interact with animated sprite from outside
	void playAnimation(int);
	void setNextAnimation(int);
	void resetAnimationFrame();

private:
	//declare the enum first so helper functions can take it as a parameter in header
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

protected:
	int animState;
	bool faceRight;
	bool *upPress, *rightPress, *downPress, *leftPress;

	int dashDirection;
	bool dashing, attacking;
	float dashTimer, attackTimer;

	bool invulnerable;
	float invulnTimer;

	bool inDialogue;
	int dialogueIndex;
	std::vector<std::string> currentDialogue;

	std::vector<AnimatedSprite*> effects;
	
	// helper methods
	void updateEffects(float delta);
	void handleDashing(float delta);
	void damageEnemiesInRect(Rectangle, int);
	void setAnimations(ANIM_STATE, ANIM_STATE);

	void findNPCforDialogue();

private:
	void move(float);

	// handle all combo attacks in each specific class, so it is private
	void combo1Attack();
};

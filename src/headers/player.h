#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>

#include "hero.h"
#include "entity.h"

/**
 * Player controller class that controls heros
 */
class Player : public Entity{

public:
    Player();
    Player(Hero*);
    ~Player();

	// getter/setter functions
	void setCollisionData(std::vector<int>, int, int);
	void setHeroEntities(std::vector<Entity*>*);
	void setPos(int, int);
	int getCenterX() const;
	int getCenterY() const;

    void handleEvents(SDL_Event);
    void update(float);
    void render(SDL_Surface*, SDL_Rect);
private:
	enum ANIM_STATE {
		IDLE_RIGHT = 0,
		IDLE_LEFT = 1,
		MOVE_RIGHT = 2,
		MOVE_LEFT = 3,
		ATTACK1RIGHT = 4,
		ATTACK1LEFT = 5
	};

    Hero * hero;

	bool moving;
	bool faceRight;
	bool moveUp, moveDown, moveRight, moveLeft;

	ANIM_STATE currentAnimation;

    void handleKeyPress(SDL_Keycode);
    void handleKeyRelease(SDL_Keycode);
	void changeAnimation();

	float attackCounter;	// keeps track of how long the current attack has gone for
	float attackBar;		// keeps track of how long the attack should last for
	bool attacking;

	void key1Attack();

};

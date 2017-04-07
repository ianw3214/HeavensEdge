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
		IDLE_UP = 2,
		IDLE_DOWN = 3,
		MOVE_RIGHT = 4,
		MOVE_LEFT = 5,
		MOVE_UP = 6,
		MOVE_DOWN = 7
	};

    Hero * hero;

	bool moving;
	bool faceUp, faceDown, faceLeft, faceRight;
	bool upPress, downPress, leftPress, rightPress;

	ANIM_STATE currentAnimation;

    void handleKeyPress(SDL_Keycode);
    void handleKeyRelease(SDL_Keycode);
	void processKeyEvents();
	void setAnimationToIdle();
	void changeAnimation();

};

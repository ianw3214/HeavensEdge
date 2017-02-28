#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

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
	int getCenterX();
	int getCenterY();

    void handleEvents(SDL_Event);
    void update(float);
    void render(SDL_Surface*, SDL_Rect);
private:
    Hero * hero;

	bool moveUp, moveDown, moveLeft, moveRight;
	bool upPress, downPress, leftPress, rightPress;

    void handleKeyPress(SDL_Keycode);
    void handleKeyRelease(SDL_Keycode);
	void processKeyEvents();
};

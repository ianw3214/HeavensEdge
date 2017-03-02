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

	// TODO: function that checks tile collision for movement
	//	- Take x and y coord and the tile it lands on as a center tile
	//	- Take the circle of tiles surrounding said tile
	//	- Take input of tiles as well as desired movement direction
	//	- If there is a block stopping the desired move direction
	//		- make sure the player doesn't move into the block
	//	- If there is an empty block but 1 or 2 surrounding blocks
	//		- Adjust player position to align with empty block if
	//		   the margin between player and desired position is close enough
	//	- Otherwise, there is no collisions
	//		- Move the player with no adjustments
};

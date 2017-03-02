#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>

#include "animatedSprite.h"

/**
 * Base hero class representing entities controllable by the player
 */
class Hero : public AnimatedSprite{

public:
    Hero(int, int);

	// getter/setter functions
	void setCollisionMap(std::vector<int>);
	void setLevelWidth(int);
	void setTileSize(int);

    void update(float);
    void render(SDL_Surface*, SDL_Rect);

    void move(int, float);
protected:
    int health;
    int speed;

	std::vector<int> collisionMap;
	int levelWidth, tileSize;
	bool checkCollision(int, int);
};

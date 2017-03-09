#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>

#include "animatedSprite.h"
#include "entity.h"

/**
 * Base hero class representing entities controllable by the player
 */
class Hero : public Entity{

public:
    Hero(int, int);
	virtual ~Hero() {};

	// getter/setter functions
	void setCollisionMap(std::vector<int>);
	void setLevelWidth(int);
	void setTileSize(int);
	void setPos(int, int);
	int getX();
	int getY();

    virtual void update(float);
    virtual void render(SDL_Surface*, SDL_Rect);

	// methods to interact with animated sprite from outside
	void playAnimation(int);

    void move(int, float);
protected:
	int x, y;
    int health;
    int speed;

	std::vector<int> collisionMap;
	int levelWidth, tileSize;
	bool checkCollision(int, int);

	AnimatedSprite * sprite;
};

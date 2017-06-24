#pragma once

#include <SDL.h>

#include "entity.h"
#include "animatedSprite.h"
#include "collision.h"

/**
 * Base creature class representing game entities with health.
 */
class Creature : public Entity{
public:
	Creature();
	Creature(int, int);
	Creature(int, int, int);
	Creature(int, int, int, int);
	Creature(int, int, int, int, int, int);

	void takeDamage(int);
	int getHealth() const;
	Shape * getCollisionBox() const;
	void setCollisionMap(std::vector<int>);
	void setTileSize(int);
	void setLevelWidth(int);
	void setCollisionData(std::vector<int>, int, int);

	void handleEvents(SDL_Event);
	void update(float);
	void render(SDL_Surface*, SDL_Rect);
	
	void move(int, int);

protected:
	int health;

	// use a pointer to prevent class slicing
	Shape * collisionBox;
	std::vector<int> collisionMap;
	int levelWidth, tileSize;

	bool checkCollision(int, int);

	int x, y;
	int collisionMarginX, collisionMarginY;

	AnimatedSprite * sprite;

	void init(int, int, int, int, int, int);

};
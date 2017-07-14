#pragma once

#include <SDL.h>

#include "entity.h"
#include "animatedSprite.h"
#include "collision.h"

#include <iostream>

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
	static void setCollisionMap(std::vector<int>);
	static void setTileSize(int);
	static void setLevelWidth(int);
	static void setCollisionData(std::vector<int>, int, int);
	static void setEntityList(std::vector<Entity*>*);

	void handleEvents(SDL_Event);
	void update(float);
	void render(SDL_Surface*, SDL_Rect);
	
	void move(int, int);

protected:
	int health;

	// use a pointer to prevent class slicing
	Shape * collisionBox;
	static std::vector<int> collisionMap;
	static int levelWidth, tileSize;
	static std::vector<Entity*>* entityList;

	bool checkCollision(int, int);

	int x, y;
	int collisionMarginX, collisionMarginY;

	AnimatedSprite * sprite;

	void init(int, int, int, int, int, int);

};
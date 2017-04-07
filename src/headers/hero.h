#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>

#include "creature.h"

/**
 * Base hero class representing entities controllable by the player
 */
class Hero : public Creature{

public:
    Hero(int, int);
	virtual ~Hero() {};

	// getter/setter functions
	void setCollisionMap(std::vector<int>);
	void setLevelWidth(int);
	void setTileSize(int);
	void setPos(int, int);
	void setEntities(std::vector<Entity*>*);
	int getX();
	int getY();

    virtual void update(float);
    virtual void render(SDL_Surface*, SDL_Rect);

	virtual void key1Attack();

	// methods to interact with animated sprite from outside
	void playAnimation(int);

    void move(int, float);
protected:
    int speed;

	std::vector<Entity*>* entityList;
	std::vector<int> collisionMap;
	int levelWidth, tileSize;
	bool checkCollision(int, int);
	void moveToEdge(int);
};

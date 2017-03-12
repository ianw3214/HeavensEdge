#pragma once

#include <SDL.h>
#include <vector>

#include "gameObject.h"
#include "animatedSprite.h"

/**
 * Abstract class providing base functions shared across entities
 */
class Entity : public GameObject{

public:
	Entity();
	Entity(int);		// Health
	Entity(int, int);	// Health + TYPE
	Entity(int, int, int, int);	// Health + TYPE + positions
	virtual ~Entity() {};	// Virtual destructor to prevent memory leaks

	// getter/setters
	void setEntities(std::vector<GameObject*>*);
	bool isDead() const;
	int getX() const;
	int getY() const;
	int getSpriteWidth() const;
	int getSpriteHeight() const;
	SDL_Rect getCollisionRect() const;

	void takeDamage(int);
	void heal(int);

protected:
	AnimatedSprite * sprite;

	int x, y;

	int health, maxHealth;
	bool dead;
	std::vector<GameObject*>* entityList;

};

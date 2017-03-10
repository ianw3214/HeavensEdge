#pragma once

#include <SDL.h>
#include <vector>

#include "gameObject.h"

/**
 * Abstract class providing base functions shared across entities
 */
class Entity : public GameObject{

public:
	Entity();
	Entity(int);		// Health
	Entity(int, int);	// Health + TYPE
	virtual ~Entity() {};	// Virtual destructor to prevent memory leaks

	// getter/setters
	void setEntities(std::vector<GameObject*>*);
	bool isDead();

	void takeDamage(int);
	void heal(int);

protected:
	int health, maxHealth;
	bool dead;
	std::vector<GameObject*>* entityList;

};

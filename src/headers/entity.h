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
	void setType(int);
	int getType();

	void takeDamage(int);
	void heal(int);

private:
	int health, maxHealth;
	bool dead;
	std::vector<GameObject*>* entityList;

	// TYPE is represented by ints for now, eventually want to move to ENUMS
	//		- 0 stands for generic types
	int TYPE;
};

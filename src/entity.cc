#include "entity.h"

#include <iostream>

// default constructor
Entity::Entity() {
	// set default values
	maxHealth = 10;
	health = 10;
	dead = false;
	TYPE = 0;		// 0 stands for a generic type
}

// constructor with health set
Entity::Entity(int initHealth) {
	maxHealth = initHealth;
	health = initHealth;
	// set default values
	dead = false;
	TYPE = 0;		// 0 stands for a generic type
}

// constructor with health and type set
Entity::Entity(int initHealth, int thisType) {
	maxHealth = initHealth;
	health = initHealth;
	TYPE = thisType;
	// set default values
	dead = false;
}

// constructor with health, type and positions set
Entity::Entity(int initHealth, int thisType, int initX, int initY) {
	maxHealth = initHealth;
	health = initHealth;
	x = initX;
	y = initY;
	TYPE = thisType;
	// set default values
	dead = false;
}

// getter/setter functions
void Entity::setEntities(std::vector<GameObject*>* input) { entityList = input; }
bool Entity::isDead() const { return dead; }
int Entity::getX() const { return x; }
int Entity::getY() const { return y; }
int Entity::getSpriteWidth() const { return sprite->getTileWidth(); }
int Entity::getSpriteHeight() const { return sprite->getTileHeight(); }
SDL_Rect Entity::getCollisionRect() const { return sprite->getCollisionRect(); }

/**
 * Decreases health of the entity
 * @param dmg The amount of damage to be taken
 */
void Entity::takeDamage(int dmg) {
	health -= dmg;
	// set the player to dead if health falls below 0
	if (health <= 0) { dead = true; }
	std::cout << "HEALTH: " << health << std::endl;		// DEBUG CODE
}

/**
 * Restores the health of the entity until the max
 * @param hp The amount of health to restore
 */
void Entity::heal(int hp) {
	health += hp;
	// set the players health to max if it goes over
	if (health > maxHealth) { health = maxHealth; }
}
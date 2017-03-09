#include "entity.h"

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
	// set default values
	dead = false;
	TYPE = thisType;
}

// getter/setter functions
void Entity::setEntities(std::vector<GameObject*>* input) { entityList = input; }
bool Entity::isDead() { return dead; }
void Entity::setType(int inputType) { TYPE = inputType; }
int Entity::getType() { return TYPE; }

/**
 * Decreases health of the entity
 * @param dmg The amount of damage to be taken
 */
void Entity::takeDamage(int dmg) {
	health -= dmg;
	// set the player to dead if health falls below 0
	if (health <= 0) { dead = true; }
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
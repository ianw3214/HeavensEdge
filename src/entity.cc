#include "entity.h"

// declare static variables
SDL_Surface* Entity::screenDisplay;

// default constructor (type set to 0)
Entity::Entity() {
	init(0);
}

// constructor with an input type
Entity::Entity(int inputType) {
	init(inputType);
}

// getter/setter methods
int Entity::getType() const { return type; }
bool Entity::getRemove() const { return REMOVE; }

void Entity::setDisplay(SDL_Surface * inputSurface) { screenDisplay = inputSurface; }

// initialization function to set default entity attributes
void Entity::init(int inputType) {
	type = inputType;
	REMOVE = false;
}
#include "gameObject.h"

/**
 * Default gameObject constructor
 *   - sets the type by default to 0
 */
GameObject::GameObject() : TYPE(0),  REMOVE(false) {}

/**
 * GameObject contructor with type initialized
 * @type type Integer representing the gameObject type
 */
GameObject::GameObject(int type) : TYPE(type), REMOVE(false) {}

// getter/setter functions for class attributes
void GameObject::setType(int inputType) { TYPE = inputType; }

int GameObject::getType() { return TYPE; }

bool GameObject::shouldRemove() { return REMOVE; }
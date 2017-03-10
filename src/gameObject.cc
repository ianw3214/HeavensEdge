#include "gameObject.h"

GameObject::GameObject() : TYPE(0),  REMOVE(false) {}

void GameObject::setType(int inputType) {
	TYPE = inputType;
}

int GameObject::getType() {
	return TYPE;
}

bool GameObject::shouldRemove() {
	return REMOVE;
}
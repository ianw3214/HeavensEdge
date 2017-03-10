#include "gameObject.h"

GameObject::GameObject() : TYPE(0) {}

void GameObject::setType(int inputType) {
	TYPE = inputType;
}

int GameObject::getType() {
	return TYPE;
}


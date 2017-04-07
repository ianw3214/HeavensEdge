#include "creature.h"

Creature::Creature() {
	sprite = nullptr;
	init(0, 0, 5);
}

Creature::Creature(int startX, int startY) {
	sprite = nullptr;
	init(startX, startY, 5);
}

Creature::Creature(int startX, int startY, int startHealth) {
	sprite = nullptr;
	init(startX, startY, startHealth);
}

void Creature::takeDamage(int dmg) { health -= dmg; }
int Creature::getHealth() const { return health; }

void Creature::handleEvents(SDL_Event) {
	// do nothing for a default creature when events are input
}

void Creature::update(float delta) {
	// do nothing for a default creature when updates are called
}

void Creature::render(SDL_Surface* display, SDL_Rect camera) {
	sprite->render(display, camera);
}

void Creature::init(int inputX, int inputY, int inputHealth) {
	x = inputX;
	y = inputY;
	health = inputHealth;
}
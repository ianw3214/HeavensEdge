#include "creature.h"

// Default constructor
Creature::Creature() {
	sprite = nullptr;
	init(0, 0, 5);
}

// Constructor with initial positions set
Creature::Creature(int startX, int startY) {
	sprite = nullptr;
	init(startX, startY, 5);
}

// Constructor with initial positions as well as starting health set.
Creature::Creature(int startX, int startY, int startHealth) {
	sprite = nullptr;
	init(startX, startY, startHealth);
}

// getter/setter and some simple methods
void Creature::takeDamage(int dmg) { health -= dmg; }
int Creature::getHealth() const { return health; }

// method for event handling, does nothing by default.
void Creature::handleEvents(SDL_Event) {
	// do nothing for a default creature when events are input
}

/**
* Updates the creature
* @param delta Difference in time between update calls
*/
void Creature::update(float delta) {
	// do nothing for a default creature when updates are called
}

/**
* Renders the hero according to camera position
* @param display SDL_Surface associated with the game window
* @param camera  SDL_Rect representing the game camera
*/
void Creature::render(SDL_Surface* display, SDL_Rect camera) {
	sprite->render(display, camera);
}

/**
 * Helper function to initialize class attributes
 * @param inputX The initial starting x position
 * @param inputY The initial starting y position
 * @param inputHealth The starting health of the creature
 */
void Creature::init(int inputX, int inputY, int inputHealth) {
	x = inputX;
	y = inputY;
	health = inputHealth;
}
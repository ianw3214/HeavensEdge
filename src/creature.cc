#include "creature.h"

// define static variables
std::vector<Entity*>* Creature::entityList;

// define static variables
std::vector<int> Creature::collisionMap;
int Creature::levelWidth, Creature::tileSize;

// Default constructor
Creature::Creature() {
	sprite = nullptr;
	init(0, 0, 5, 0, 0, 0);
}

// Constructor with initial positions set
Creature::Creature(int startX, int startY) {
	sprite = nullptr;
	init(startX, startY, 5, 0, 0, 0);
}

// Constructor with initial positions as well as starting health set.
Creature::Creature(int startX, int startY, int startHealth) {
	sprite = nullptr;
	init(startX, startY, startHealth, 0, 0, 0);
}

// Constructor with initial positions, starting health, and type set.
Creature::Creature(int startX, int startY, int startHealth, int inpType) {
	sprite = nullptr;
	init(startX, startY, startHealth, inpType, 0, 0);
}

// Constructor with initial positions, starting health, type, and collision margins set
Creature::Creature(int startX, int startY, int startHealth, int inpType, int cMarginX, int cMarginY) {
	sprite = nullptr;
	init(startX, startY, startHealth, inpType, cMarginX, cMarginY);
}

// getter/setter and some simple methods
void Creature::takeDamage(int dmg) { health -= dmg; }
int Creature::getX() const { return x; }
int Creature::getY() const { return y; }
int Creature::getHealth() const { return health; }
Shape * Creature::getCollisionBox() const { return collisionBox; }
void Creature::setCollisionMap(std::vector<int> inputMap) { collisionMap = inputMap; }
void Creature::setTileSize(int size) { tileSize = size; }
void Creature::setLevelWidth(int width) { levelWidth = width; }
void Creature::setCollisionData(std::vector<int> a, int b, int c) {
	setCollisionMap(a);
	setLevelWidth(b);
	setTileSize(c);
}
void Creature::setEntityList(std::vector<Entity*>* inputList) {
	entityList = inputList;
}

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
* Moves the hero in a certain direction
* @param direction Integer representation of hero movement direction
* @param delta     Delta time to account for when calculating move distance
*/
void Creature::move(int direction, int units) {
	// 0 - up, 1 - right, 2 - down, 3 - left
	// get the amount of units that the hero should move this update call
	int newX = x;
	int newY = y;
	// calculate the new position
	if (direction == 0) { newY -= units; }
	else if (direction == 1) { newX += units; }
	else if (direction == 2) { newY += units; }
	else if (direction == 3) { newX -= units; }
	// if a collision occured, move by 1 pixel until collision again
	if (checkCollision(newX, newY)) {
		int lastX = newX = x;
		int lastY = newY = y;
		while (!checkCollision(newX, newY)) {
			lastX = newX;
			lastY = newY;
			if (direction == 0) { newY -= 1; }
			else if (direction == 1) { newX += 1; }
			else if (direction == 2) { newY += 1; }
			else if (direction == 3) { newX -= 1; }
		}
		x = lastX;
		y = lastY;
	}
	else {
		// otherwise, set the new x and y positions
		x = newX;
		y = newY;
	}
}

/**
 * Helper function to initialize class attributes
 * @param inputX The initial starting x position
 * @param inputY The initial starting y position
 * @param inputHealth The starting health of the creature
 */
void Creature::init(int inputX, int inputY, int inputHealth, int inpType, int cMarginX, int cMarginY) {
	x = inputX;
	y = inputY;
	health = inputHealth;
	type = inpType;
	// set the collision box to a 0 by 0 square by default
	collisionBox = new Rectangle(x, y, 0, 0);
	collisionMarginX = cMarginX;
	collisionMarginY = cMarginY;
}

/**
* Checks the hero the see if it collides with a collidable tile
*/
bool Creature::checkCollision(int xpos, int ypos) {
	// TODO: check if player goes out of the map
	std::vector<int> checkIndices;			// vector to hold indices of collision map to check
	// get the players left and up most tile box
	int tileX = static_cast<int>(xpos / tileSize);
	int tileY = static_cast<int>(ypos / tileSize);
	// we only have to check 4 boxes because the player spans at most 4 tiles
	// since x and y round down, we know we only have to get the right and bottom tiles
	int targetIndex = tileY * levelWidth + tileX;
	checkIndices.push_back(targetIndex);	// add the current tile always
	// if we aren't at the right most side of the level, add the tile 1 to the right
	if (tileX != levelWidth - 1) { checkIndices.push_back(targetIndex + 1); }
	// if we aren't at the bottom, add the bottom 2 tiles
	if ((tileY + 1) * levelWidth < collisionMap.size()) {
		checkIndices.push_back(targetIndex + levelWidth);
		checkIndices.push_back(targetIndex + levelWidth + 1);
	}
	for (unsigned int i = 0; i < checkIndices.size(); i++) {
		int collisionIndex = checkIndices.at(i);
		if (collisionMap.at(collisionIndex) == 1) {	// 1 means it is a collidable tile
			// check the coords of the tile against player position
			int targetX = (collisionIndex % levelWidth) * tileSize;
			int targetY = static_cast<int>(collisionIndex / levelWidth) * tileSize;
			// make rectangles to represent the collision simulation
			Rectangle target(targetX, targetY, 64, 64);
			Rectangle newCollisionBox(*static_cast<Rectangle*>(collisionBox));
			newCollisionBox.x = xpos + collisionMarginX;
			newCollisionBox.y = ypos + collisionMarginY;
			if (isColliding(newCollisionBox, target)) {
				// return true only if both x and y intersect
				return true;
			}
		}
	}
	// return false if no collision happened
	return false;
}
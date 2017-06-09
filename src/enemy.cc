#include "enemy.h"

// define the static variables of the header file
std::vector<int> Enemy::collisionMap;
int Enemy::levelWidth, Enemy::tileSize;

/**
 * Default enemy constructor
 */
Enemy::Enemy() : Creature(0, 0, 10, 2) , speed(200) {
	// set default variables
	init();
}

/**
 * Enemy constructor with initial positions
 * @param initX Integer corresponding to the initial x position
 * @param initY Integer corresponding to the initial y position
 */
Enemy::Enemy(int initX, int initY) : Creature(initX, initY, 10, 2), speed(200) {
	init();
}

// getter/setter methods
void Enemy::setCollisionMap(std::vector<int> inputMap) { Enemy::collisionMap = inputMap; }
void Enemy::setLevelWidth(int width) { Enemy::levelWidth = width; }
void Enemy::setTileSize(int size) { Enemy::tileSize = size; }
void Enemy::setCollisionData(std::vector<int> map, int width, int tileSize) {
	Enemy::setCollisionMap(map);
	Enemy::setLevelWidth(width);
	Enemy::setTileSize(tileSize);
}

/**
* Update the enemy
* @param delta Difference in time between update calls
*/
void Enemy::update(float delta) {
	sprite->update(delta);
	sprite->setPos(x, y);
	if (health <= 0) {
		REMOVE = true;
	}
	// update enemy movement
	move(delta);
	// update movement direction when timer is up
	if (moveTime > 0.7f) {
		moveTime = 0.0f;
		currentDir = rand() % 4;
	}
	else moveTime += delta;
	// update the collision rectangle as well
	collisionBox->x = x;
	collisionBox->y = y;
}

/**
* Renders the enemy according to camera position
* @param display SDL_Surface associated with the game window
* @param camera  SDL_Rect representing the game camera
*/
void Enemy::render(SDL_Surface * display, SDL_Rect camera) {
	sprite->render(display, camera);
}

/**
 * Initializes basic enemy attributes
 *   - helper functions for the constructors
 */
void Enemy::init() {
	sprite = new AnimatedSprite("assets/enemy.png", 64, 64, 1, false);
	sprite->setAnimationData({ 1 });
	// set the default collision rectangle
	collisionBox = new Rectangle(x, y, 64, 64);
	// set the initial movement flags
	currentDir = rand() % 4;
	moveTime = 0.0f;
}

void Enemy::move(float delta) {
	// 0 - up, 1 - right, 2 - down, 3 - left
	// get the amount of units that the hero should move this update call
	int units = static_cast<int>(speed*delta);
	int newX = x;
	int newY = y;
	// calculate the new position
	if (currentDir == 0) { newY -= units; }
	else if (currentDir == 1) { newX += units; }
	else if (currentDir == 2) { newY += units; }
	else if (currentDir == 3) { newX -= units; }
	// if a collision occured, move by 1 pixel until collision again
	if (checkCollision(newX, newY)) {
		int lastX = newX = x;
		int lastY = newY = y;
		while (!checkCollision(newX, newY)) {
			lastX = newX;
			lastY = newY;
			if (currentDir == 0) { newY -= 1; }
			else if (currentDir == 1) { newX += 1; }
			else if (currentDir == 2) { newY += 1; }
			else if (currentDir == 3) { newX -= 1; }
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

bool Enemy::checkCollision(int xpos, int ypos) {
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
			newCollisionBox.x = xpos;
			newCollisionBox.y = ypos;
			if (isColliding(newCollisionBox, target)) {
				// return true only if both x and y intersect
				return true;
			}
		}
	}
	// return false if no collision happened
	return false;
}
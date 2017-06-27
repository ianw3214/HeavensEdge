#include "enemy.h"

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
	if (idleTimer > 0.0f) {
		idleTimer -= delta;
		if (idleTimer < 0.0f) idleTimer = 0.0f;
	}
	else {
		move(delta);
		int key = rand() % 200;
		if (key == 5) {
			idleTimer = 1.5f;
			currentDir = rand() % 4;
		}
	}
	// update the collision rectangle as well
	collisionBox->x = x + collisionMarginX;
	collisionBox->y = y + collisionMarginY;
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
	idleTimer = 0.0f;
	width = 64;
	height = 64;
}

void Enemy::move(float delta) {
	Creature::move(currentDir, speed * delta);
}
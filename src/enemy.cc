#include "enemy.h"

/**
 * Default enemy constructor
 */
Enemy::Enemy() : Entity(10, 2, 0, 0) {
	// set default variables
	init();
}

/**
 * Enemy constructor with initial positions
 * @param initX Integer corresponding to the initial x position
 * @param initY Integer corresponding to the initial y position
 */
Enemy::Enemy(int initX, int initY) : Entity(10, 2, initX, initY) {
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
	sprite->setCollisionRect(sprite->getTileWidth(), sprite->getTileHeight());
}
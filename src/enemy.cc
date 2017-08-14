#include "enemy.h"

/**
 * Default enemy constructor
 */
Enemy::Enemy() : Creature(0, 0, 10, 3) {
	// set default variables
	init();
}

/**
 * Enemy constructor with initial positions
 * @param initX Integer corresponding to the initial x position
 * @param initY Integer corresponding to the initial y position
 */
Enemy::Enemy(int initX, int initY) : Creature(initX, initY, 10, 3) {
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
		// update the animation state
		if (currentDir == 0)
			animState = 2;
		if (currentDir == 1)
			animState = 1;
		if (currentDir == 2)
			animState = 0;
		if (currentDir == 3)
			animState = 3;
	}
	else {
		move(delta);
		int key = rand() % 200;
		if (key == 5) {
			idleTimer = ENEMY::IDLE_TIME;
			currentDir = rand() % 4;
		}
		// update the animation state
		if (currentDir == 0)
			animState = 6;
		if (currentDir == 1)
			animState = 5;
		if (currentDir == 2)
			animState = 4;
		if (currentDir == 3)
			animState = 7;
	}
	// update the collision rectangle as well
	collisionBox->x = x + collisionMarginX;
	collisionBox->y = y + collisionMarginY;
	sprite->playAnimation(animState);
}

/**
* Renders the enemy according to camera position
* @param display SDL_Surface associated with the game window
* @param camera  SDL_Rect representing the game camera
*/
void Enemy::render(SDL_Renderer * renderer, SDL_Rect camera) {
	sprite->render(renderer, camera);
}

/**
 * Initializes basic enemy attributes
 *   - helper functions for the constructors
 */
void Enemy::init() {
	sprite = new AnimatedSprite(SPRITE_ID::ENEMY, ENEMY::SPRITE_WIDTH, ENEMY::SPRITE_HEIGHT, ENEMY::SPRITESHEET_WIDTH, false);
	sprite->setAnimationData({ 1, 1, 1, 1, 2, 2, 2, 2 });
	// set the default collision rectangle
	collisionBox = new Rectangle(x, y, ENEMY::COLLISION_WIDTH, ENEMY::COLLISION_HEIGHT);
	// set the initial movement flags
	currentDir = rand() % 4;
	idleTimer = 0.0f;
	// set collision margins
	collisionMarginX = ENEMY::COLLISION_SPRITE_MARGIN_X;
	collisionMarginY = ENEMY::COLLISION_SPRITE_MARGIN_Y;
	// by default, look down
	animState = 0;
}

void Enemy::move(float delta) {
	Creature::move(currentDir, static_cast<int>(ENEMY::SPEED * delta));
}
#include "enemy.h"

Enemy::Enemy() : Entity(10, 2, 0, 0) {
	// set default variables
	init();
}

Enemy::Enemy(int initX, int initY) : Entity(10, 2, initX, initY) {
	init();
}

void Enemy::update(float delta) {
	sprite->update(delta);
	sprite->setPos(x, y);
	if (health <= 0) {
		REMOVE = true;
	}
}

void Enemy::render(SDL_Surface * display, SDL_Rect camera) {
	sprite->render(display, camera);
}

void Enemy::init() {
	sprite = new AnimatedSprite("assets/enemy.png", 64, 64, 1, false);
	sprite->setAnimationData({ 1 });
	sprite->setCollisionRect(sprite->getTileWidth(), sprite->getTileHeight());
}
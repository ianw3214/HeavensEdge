#include "enemy.h"

Enemy::Enemy() : Entity(10, 2) {
	// set default variables
	x = 0;
	y = 0;
	init();
}

Enemy::Enemy(int initX, int initY) : Entity(10, 2), x(initX), y(initY) {
	init();
}

void Enemy::update(float delta) {
	sprite->update(delta);
	sprite->setPos(x, y);
}

void Enemy::render(SDL_Surface * display, SDL_Rect camera) {
	sprite->render(display, camera);
}

void Enemy::init() {
	sprite = new AnimatedSprite("assets/enemy.png", 64, 64, 1, false);
	sprite->setAnimationData({ 1 });
}
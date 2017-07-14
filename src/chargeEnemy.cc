#include "chargeEnemy.h"

ChargeEnemy::ChargeEnemy() {
	init(0, 0);
}

ChargeEnemy::ChargeEnemy(int startX, int startY){
	init(startX, startY);
}

void ChargeEnemy::update(float delta) {
	// update the position/animations of the sprite
	sprite->update(delta);
	sprite->setPos(x, y);
	// update the collision box as well
	collisionBox->x = x + collisionMarginX;
	collisionBox->y = y + collisionMarginY;
	// remove the enemy if it's health is below 0
	if (health <= 0) {
		REMOVE = true;
	}
}

void ChargeEnemy::render(SDL_Surface * display, SDL_Rect camera) {
	sprite->render(display, camera);
}

void ChargeEnemy::init(int inpX, int inpY) {
	sprite = new AnimatedSprite("assets/ChargeEnemy.png", 64, 64, 1, false);
	sprite->setAnimationData({ 1 });
	// set the default collision rectangle
	collisionBox = new Rectangle(x, y, 64, 64);
	x = inpX, y = inpY;
	health = 10;
	type = 3;
}
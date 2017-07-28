#include "chargeEnemy.h"

ChargeEnemy::ChargeEnemy() : Enemy() {
	init(0, 0);
}

ChargeEnemy::ChargeEnemy(int startX, int startY) : Enemy() {
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
	// if the creature is not charging, determine if it should
	if (!charging) {
		// make 4 collision lines to determine if the player is within sight
		Line up(x + 32, y + 32, x + 32, y - 400 + 32);
		Line right(x + 32, y + 32, x + 400 + 32, y + 32);
		Line down(x + 32, y + 32, x + 32, y + 400 + 32);
		Line left(x + 32, y + 32, x - 400 + 32, y + 32);
		if (isColliding(up, *(hero->getCollisionBox()))) {
			charging = true;
			direction = 0;
		}
		else if (isColliding(right, *(hero->getCollisionBox()))) {
			charging = true;
			direction = 1;
		}
		else if (isColliding(down, *(hero->getCollisionBox()))) {
			charging = true;
			direction = 2;
		}
		else if (isColliding(left, *(hero->getCollisionBox()))) {
			charging = true;
			direction = 3;
		}
	}
	// otherwise, update the creature accordingly
	else {
		Creature::move(direction, static_cast<int>(CHARGE_ENEMY::CHARGESPEED * delta));
		// update the timer
		chargeTimer += delta;
		if (chargeTimer >= CHARGE_ENEMY::CHARGE_TIME) {
			chargeTimer = 0.0f;
			charging = false;
		}
		// only damage the player if the enemy is charging
		if (isColliding(*collisionBox, *hero->getCollisionBox())) {
			hero->takeDamage(3);
		}
	}
}

void ChargeEnemy::render(SDL_Renderer* renderer, SDL_Rect camera) {
	sprite->render(renderer, camera);
}

void ChargeEnemy::init(int inpX, int inpY) {
	// set default variables
	charging = false;
	direction = 0;
	chargeTimer = 0.0f;
	// set the enemy sprite
	sprite = new AnimatedSprite(SPRITE_ID::CHARGE_ENEMY, CHARGE_ENEMY::SPRITE_WIDTH, CHARGE_ENEMY::SPRITE_HEIGHT, CHARGE_ENEMY::SPRITESHEET_WIDTH, false);
	sprite->setAnimationData({ 1 });
	// set the default collision rectangle
	collisionBox = new Rectangle(x, y, CHARGE_ENEMY::COLLISION_WIDTH, CHARGE_ENEMY::COLLISION_HEIGHT);
	collisionMarginX = CHARGE_ENEMY::COLLISION_SPRITE_MARGIN_X;
	collisionMarginY = CHARGE_ENEMY::COLLISION_SPRITE_MARGIN_Y;
	// set other variables
	x = inpX, y = inpY;
	health = 10;
	type = 3;
	// look for the hero from the entity list
	for (unsigned int i = 0; i < Creature::entityList->size(); i++) {
		if (entityList->at(i)->getType() == 2) {
			Player * temp = dynamic_cast<Player*>(entityList->at(i));
			hero = dynamic_cast<Hero*>(temp->getHero());
		}
	}
	if (!hero) std::cout << "ERROR: Could not find a hero entity." << std::endl;
}
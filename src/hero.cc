#include "hero.h"

#include <iostream>
#include <cmath>

/**
 * Default constructor with initial positions
 *
 * Calls the Entity constructor with 20 base health
 */
Hero::Hero(int initX, int initY) : Creature (initX, initY, 5, 2, HERO::COLLISION_SPRITE_MARGIN_X, HERO::COLLISION_SPRITE_MARGIN_Y) {
    // TODO: get default variables from input/global variable/something like that
	sprite = new AnimatedSprite("assets/hero.png", 64, 64, 10, false);
    sprite->setAnimationData({10, 10, 6, 6, 10, 10});
	dashTimer = 0.0f;
	dashDirection = -1;
	// initialize the collision shape
	collisionBox = new Rectangle(x, y, HERO::COLLISION_WIDTH, HERO::COLLISION_HEIGHT);
	width = HERO::COLLISION_WIDTH;
	height = HERO::COLLISION_HEIGHT;
}

// getter/setter functions
void Hero::setPos(int newX, int newY) { x = newX, y = newY; }
void Hero::setEntities(std::vector<Entity*>* input) { entityList = input; }
int Hero::getX() const { return x; }
int Hero::getY() const { return y; }

/**
 * Updates the hero
 * @param delta Difference in time between update calls
 */
void Hero::update(float delta){
	Creature::update(delta);
    sprite->update(delta);
	// set the position of the sprite to match that of the hero
	sprite->setPos(x, y);
	// update the collision shape as well
	collisionBox->x = x + collisionMarginX;
	collisionBox->y = y + collisionMarginY;
	// delete effects accordingly
	for (int i = effects.size() - 1; i >= 0; i--) {
		effects.at(i)->update(delta);
		if (effects.at(i)->getRemove()) {
			AnimatedSprite* effect = effects.at(i);
			effects.erase(effects.begin() + i);
			delete effect;
		}
	}
	// update the dash timer if it isn't 0
	if (dashTimer > 0.0f) {
		dashTimer -= delta;
		if (dashTimer <= 0.0f) {
			dashing = false;
			dashTimer = 0.0f;
		}
	}
	// update movement if the hero is dashing
	if (dashing) {
		int distance = delta / 0.2f * HERO::DASH_DISTANCE;
		if (dashDirection == 0 || dashDirection == 2) {
			int newY = (dashDirection == 0 ? -distance : distance) + y;
			// if a collision occured, move by 1 pixel until collision again
			if (checkCollision(x, newY)) {
				int lastY = newY = y;
				while (!checkCollision(x, newY)) {
					lastY = newY;
					newY += dashDirection == 0 ? -1 : 1;
				}
				y = lastY;
			}
			else { y = newY; }
		}
		else {
			int newX = (dashDirection == 1 ? distance : -distance) + x;
			// if a collision occured, move by 1 pixel until collision again
			if (checkCollision(newX, y)) {
				int lastX = newX = x;
				while (!checkCollision(newX, y)) {
					lastX = newX;
					newX += dashDirection == 1 ? 1 : -1;
				}
				x = lastX;
			}
			else { x = newX; }
		}
	}
}

/**
 * Renders the hero according to camera position
 * @param display SDL_Surface associated with the game window
 * @param camera  SDL_Rect representing the game camera
 */
void Hero::render(SDL_Surface * display, SDL_Rect camera){
    sprite->render(display, camera);
	// call the render on any function associated with the player
	for (unsigned int i = 0; i < effects.size(); i++) {
		effects.at(i)->render(display, camera);
	}
}

/**
 * Performs the attack associated with the first attack key
 * @param direction the direction the player is performing the attack
 *
 *	- Direction 0 for left, 1 for right
 */
void Hero::key1Attack(int direction) {
	// set up the collision rectangle for determing attack collisions with enemy
	Rectangle attackCollision(getX(), getY(), HERO::ATTACK_1_WIDTH, HERO::ATTACK_1_HEIGHT);
	if (direction == 0) {
		attackCollision.x -= 64;
	}
	// loop through all entities and deal damage if enemy type
	if (!entityList) { return; }
	for (unsigned int i = 0; i < entityList->size(); i++) {
		if (entityList->at(i)->getType() == 2) {
			// cast the type to an entity to access it's functions
			Creature * temp = dynamic_cast<Creature*>(entityList->at(i));
			// check for collisions
			if (isColliding(attackCollision, *temp->getCollisionBox())) {
				temp->takeDamage(5);
			}
		}
	}
	// add an attack effect to the player
	AnimatedSprite* effect = new AnimatedSprite("assets/attack.png", 100, 64, 10, true);
	effect->setAnimationData({ 10 , 10});
	if (direction == 1) { 
		effect->setPos(getX(), getY()); 
		effect->playAnimation(0);
	} else { 
		effect->setPos(getX()-36, getY()); 
		effect->playAnimation(1);
	}
	effects.push_back(effect);
}

/**
 * Performs the attack associated with the second attack key, which is a dash attack
 * @param direction The direction of the attack
 *
 *	- Direction: 0 - up, 1 - right, 2 - down, 3 - left
 */
void Hero::key2Attack(int direction) {
	dashing = true;
	dashTimer = 0.2f;
	dashDirection = direction;
}

int Hero::getKey1Cooldown() { return HERO::ATTACK_1_TIME; }
int Hero::getKey2Cooldown() { return HERO::ATTACK_2_TIME; }

/**
 * Relays the animation information to the animated sprite
 * @param anim The integer representation of the row of animation to play
 */
void Hero::playAnimation(int anim) {
	sprite->playAnimation(anim);
}

/**
 * Sets the next played sprite for the animated sprite after current one finishes playing
 * @param anim The integer representation of the row of animation to play
 */
void Hero::setNextAnimation(int anim) {
	sprite->setNextAnimation(anim);
}

/**
 * Resets the animated sprite to 1st frame
 */
void Hero::resetAnimationFrame() {
	sprite->resetAnimationFrame();
}

void Hero::move(int direction, float delta) {
	if (dashing) {
		return;
	}
	int units = HERO::BASE_SPEED * delta;
	Creature::move(direction, units);
}
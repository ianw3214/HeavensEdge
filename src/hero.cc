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
    sprite->setAnimationData({10, 10, 6, 6, 10, 10, 10, 10, 10, 10});
	// initialize dash variables
	dashTimer = 0.0f, dashDirection = -1;
	// initialize the collision shape
	collisionBox = new Rectangle(x, y, HERO::COLLISION_WIDTH, HERO::COLLISION_HEIGHT);
	// initialize attack variables
	attacking = false, attackTimer = 0.0f;
	// initialize movement flags
	upPress = false, rightPress = false, downPress = false, leftPress = false, faceRight = true;
	// initialize invulnerable variables
	invulnerable = false, invulnTimer = 0.0f;
}

// getter/setter functions
void Hero::setPos(int newX, int newY) { x = newX, y = newY; }
int Hero::getX() const { return x; }
int Hero::getY() const { return y; }
void Hero::syncMoveKeys(bool* up, bool* right, bool* down, bool* left) {
	upPress = up;
	rightPress = right;
	downPress = down;
	leftPress = left;
}

/**
 * Damages the hero by a certain amount of health
 * @param dmg The amount of damage to be taken by the hero
 */
void Hero::takeDamage(int dmg) {
	// only damage the hero if it isn't invulnerable
	if (!invulnerable) {
		health -= dmg;
		// if the hero is damaged, make it invulnerable for a short time
		invulnerable = true;
		invulnTimer = HERO::INVULN_TIME;
	}
}

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
	// update the effects
	updateEffects(delta);
	// update movement if the hero is dashing
	if (dashing) {
		handleDashing(delta);
	}
	else if (attacking) {
		// update the attack timer
		attackTimer -= delta;
		if (attackTimer <= 0.0f) attacking = false,	attackTimer = 0.0f;
	}
	else {
		// move the player according to key presses
		move(delta);
	}
	// update the invulnerability timer if the player is invulnerable
	if (invulnerable) {
		invulnTimer -= delta;
		if (invulnTimer <= 0.0f) invulnerable = false, invulnTimer = 0.0f;
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
void Hero::key1Attack() {
	// exit the function if the attack shouldn't execute
	if (attacking) return;
	if (dashing) { combo1Attack(); return; }
	// set up the collision rectangle for determing attack collisions with enemy
	Rectangle attackCollision(getX(), getY(), HERO::ATTACK_1_WIDTH, HERO::ATTACK_1_HEIGHT);
	if (!faceRight) attackCollision.x -= 64;
	// loop through all entities and deal damage if enemy type
	damageEnemiesInRect(attackCollision, HERO::ATTACK_1_DAMAGE);
	// create a new effect for the attack
	AnimatedSprite* effect = new AnimatedSprite("assets/attack.png", 100, 64, 10, true);
	effect->setAnimationData({ 10 , 10});
	effect->playAnimation(faceRight ? 0 : 1);
	effect->setPos(getX() - (faceRight ? 0 : 36), getY());
	// push the new effect to the effects vector
	effects.push_back(effect);
	// set the attack timer
	attackTimer = HERO::ATTACK_1_TIME;
	attacking = true;
	// update animations
	setAnimations(faceRight ? ATTACK1RIGHT : ATTACK1LEFT, faceRight ? IDLE_RIGHT : IDLE_LEFT);
	// play a sound
	Mix_Chunk * temp = Mix_LoadWAV("assets/sounds/atk.wav");
	Mix_PlayChannel(-1, temp, 0);
}

/**
 * Performs the attack associated with the second attack key, which is a dash attack
 * @param direction The direction of the attack
 *
 *	- Direction: 0 - up, 1 - right, 2 - down, 3 - left
 */
void Hero::key2Attack() {
	if (dashing || attacking) return;
	dashing = true;
	dashTimer = 0.2f;
	if (*upPress) dashDirection = 0;
	else if (*rightPress) dashDirection = 1;
	else if (*downPress) dashDirection = 2;
	else if (*leftPress) dashDirection = 3;
	else dashDirection = faceRight ? 1 : 3;
	// update animations
	setAnimations(faceRight ? DASH_RIGHT : DASH_LEFT, faceRight ? IDLE_RIGHT : IDLE_LEFT);
	// make the player invulnerable while dashing
	invulnerable = true;
	invulnTimer = HERO::ATTACK_2_TIME;
}

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

/**
 * moves the player a certain direction and updates animations according to movement
 * @param delta The time elapsed between the last update and the current update
 */
void Hero::move(float delta) {
	if (attacking || dashing) return;
	// update animations accordingly if the hero is not moving
	if (!*upPress && !*rightPress && !*downPress && !*leftPress) {
		animState = faceRight ? IDLE_RIGHT : IDLE_LEFT;
		playAnimation(animState);
		return;
	}
	// move a certain distance based on the delta time
	int moveDistance = static_cast<int>(delta * HERO::BASE_SPEED);
	if (*upPress) {
		Creature::move(0, moveDistance);
	}
	if (*rightPress) {
		Creature::move(1, moveDistance);
		faceRight = true;
	}
	if (*downPress) {
		Creature::move(2, moveDistance);
	}
	if (*leftPress) {
		Creature::move(3, moveDistance);
		faceRight = false;
	}
	// update the animations (up to this point, the hero is definitely moving)
	if (faceRight) animState = MOVE_RIGHT;
	else animState = MOVE_LEFT;
	sprite->playAnimation(animState);
}

/**
 * Performs an area of effect attack 
 *   - Triggered when attacking while dashing
 */
void Hero::combo1Attack() {
	// stop dashing and perform a combo attack
	dashing = false;
	dashTimer = 0.0f;
	// start attack timer again
	attacking = true;
	attackTimer = HERO::COMBO_1_TIME;
	// update animations
	setAnimations(faceRight ? COMBO1_RIGHT : COMBO1_LEFT, faceRight ? IDLE_RIGHT : IDLE_LEFT);
	// update the enemies to take damage
	// set up the collision rectangle for determing attack collisions with enemy
	Rectangle attackCollision(getX() - HERO::COMBO1_MARGIN_X, getY() - HERO::COMBO1_MARGIN_Y, HERO::COMBO1_WIDTH, HERO::COMBO1_HEIGHT);
	// loop through all entities and deal damage if enemy type
	damageEnemiesInRect(attackCollision, HERO::COMBO1_DAMAGE);
	// make the player invulnerable
	invulnerable = true;
	invulnTimer = HERO::COMBO_1_TIME;
}

// HELPER FUNCTIONS ========================================================================

void Hero::updateEffects(float delta) {
	// delete effects accordingly
	for (int i = effects.size() - 1; i >= 0; i--) {
		effects.at(i)->update(delta);
		if (effects.at(i)->getRemove()) {
			AnimatedSprite* effect = effects.at(i);
			effects.erase(effects.begin() + i);
			delete effect;
		}
	}
}

void Hero::handleDashing(float delta) {
	// update the dash timer
	dashTimer -= delta;
	if (dashTimer <= 0.0f) {
		dashing = false;
		dashTimer = 0.0f;
	}
	int distance = static_cast<int>(delta / 0.2f * HERO::DASH_DISTANCE);
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

void Hero::damageEnemiesInRect(Rectangle inputRect, int damage) {
	if (!Creature::entityList) { return; }
	for (unsigned int i = 0; i < Creature::entityList->size(); i++) {
		if (Creature::entityList->at(i)->getType() == 3) {
			// cast the type to an entity to access it's functions
			Creature * temp = dynamic_cast<Creature*>(Creature::entityList->at(i));
			// check for collisions
			if (isColliding(inputRect, *temp->getCollisionBox())) {
				temp->takeDamage(damage);
			}
		}
	}
}

void Hero::setAnimations(ANIM_STATE currentAnim, ANIM_STATE nextAnim) {
	animState = currentAnim;
	setNextAnimation(nextAnim);
	playAnimation(animState);
	resetAnimationFrame();
}
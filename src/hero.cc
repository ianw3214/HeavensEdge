#include "hero.h"

#include <iostream>
#include <cmath>

/**
 * Default constructor with initial positions
 *
 * Calls the Entity constructor with 20 base health
 */
Hero::Hero(int initX, int initY) : Creature (initX, initY, 5), speed(300), dashDistance(300) {
    // TODO: get default variables from input/global variable/something like that
	sprite = new AnimatedSprite("assets/hero.png", 64, 64, 10, false);
    sprite->setAnimationData({10, 10, 6, 6, 10, 10});
	dashTimer = 0.0f;
	dashDirection = -1;
	// initialize the collision shape
	collisionBox = new Rectangle(x, y, 56, 56);
}

// getter/setter functions
void Hero::setCollisionMap(std::vector<int> inputMap) { collisionMap = inputMap; }
void Hero::setLevelWidth(int width) { levelWidth = width; }
void Hero::setTileSize(int size) { tileSize = size; }
void Hero::setPos(int newX, int newY) { x = newX, y = newY; }
void Hero::setEntities(std::vector<Entity*>* input) { entityList = input; }
int Hero::getX() const { return x; }
int Hero::getY() const { return y; }

/**
 * Updates the hero
 * @param delta Difference in time between update calls
 */
void Hero::update(float delta){
    sprite->update(delta);
	// set the position of the sprite to match that of the hero
	sprite->setPos(x, y);
	// update the collision shape as well
	collisionBox->x = x + 4;
	collisionBox->y = y + 4;
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
		int distance = delta / 0.2f * dashDistance;
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
	Rectangle attackCollision(getX(), getY(), 100, 64);
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

void Hero::key2Attack(int direction) {
	dashing = true;
	dashTimer = 0.2f;
	dashDirection = direction;
}

/**
 * Relays the animation information to the animated sprite
 * @param anim The integer representation of the row of animation to play
 */
void Hero::playAnimation(int anim) {
	sprite->playAnimation(anim);
}

void Hero::setNextAnimation(int anim) {
	sprite->setNextAnimation(anim);
}

void Hero::resetAnimationFrame() {
	sprite->resetAnimationFrame();
}

/**
 * Moves the hero in a certain direction
 * @param direction Integer representation of hero movement direction
 * @param delta     Delta time to account for when calculating move distance
 */
void Hero::move(int direction, float delta){
	// don't move the hero if the hero is in the middle of a dash
	if (dashing) {
		return;
	}
    // 0 - up, 1 - right, 2 - down, 3 - left
	// get the amount of units that the hero should move this update call
	int units = static_cast<int>(speed*delta);
	int newX = x;
	int newY = y;
	// calculate the new position
	if (direction == 0) { newY -= units; }
	else if (direction == 1) { newX += units; }
	else if (direction == 2) { newY += units; }
	else if (direction == 3) { newX -= units; }
	// if a collision occured, move by 1 pixel until collision again
	if (checkCollision(newX, newY)) {
		int lastX = newX = x;
		int lastY = newY = y;
		while (!checkCollision(newX, newY)) {
			lastX = newX;
			lastY = newY;
			if (direction == 0) { newY -= 1; }
			else if (direction == 1) { newX += 1; }
			else if (direction == 2) { newY += 1; }
			else if (direction == 3) { newX -= 1; }
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

/**
 * Checks the hero the see if it collides with a collidable tile
 */
bool Hero::checkCollision(int xpos, int ypos) {
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
	if(tileX != levelWidth-1){ checkIndices.push_back(targetIndex + 1); }
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
			newCollisionBox.x = xpos + 4;
			newCollisionBox.y = ypos + 4;
			if (isColliding(newCollisionBox, target)){
				// return true only if both x and y intersect
				return true;
			}
		}
	}
	// return false if no collision happened
	return false;
}
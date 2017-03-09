#include "hero.h"

#include <iostream>
#include <cmath>

/**
 * Default constructor with initial positions
 */
Hero::Hero(int initX, int initY) {
    // TODO: get default variables from input/global variable/something like that
	sprite = new AnimatedSprite("assets/hero.png", 64, 64, 10, false);
    sprite->setAnimationData({10, 10, 10, 10, 10, 10, 10, 10});
    x = initX;
    y = initY;
    health = 5;
    speed = 300;
}

// getter/setter functions
void Hero::setCollisionMap(std::vector<int> inputMap) { collisionMap = inputMap; }
void Hero::setLevelWidth(int width) { levelWidth = width; }
void Hero::setTileSize(int size) { tileSize = size; }
void Hero::setPos(int newX, int newY) { x = newX, y = newY; }
int Hero::getX() { return x; }
int Hero::getY() { return y; }

/**
 * Updates the hero
 * @param delta Difference in time between update calls
 */
void Hero::update(float delta){
    sprite->update(delta);
	// set the position of the sprite to match that of the hero
	sprite->setPos(x, y);
}

/**
 * Renders the hero according to camera position
 * @param display SDL_Surface associated with the game window
 * @param camera  SDL_Rect representing the game camera
 */
void Hero::render(SDL_Surface * display, SDL_Rect camera){
    sprite->render(display, camera);
}

/**
 * Relays the animation information to the animated sprite
 * @param anim The integer representation of the row of animation to play
 */
void Hero::playAnimation(int anim) {
	sprite->playAnimation(anim);
}

/**
 * Moves the hero in a certain direction
 * @param direction Integer representation of hero movement direction
 * @param delta     Delta time to account for when calculating move distance
 */
void Hero::move(int direction, float delta){
    // 0 - up, 1 - right, 2 - down, 3 - left
	int units = static_cast<int>(speed*delta);
	int newX = x;
	int newY = y;
	if (direction == 0) { newY -= units; }
	if (direction == 1) { newX += units; }
	if (direction == 2) { newY += units; }
	if (direction == 3) { newX -= units; }
	// if a collision occured, check for a small margin
	if (checkCollision(newX, newY)) {
		// check if the margin is small enough for the player to be adjusted
		if (direction == 0 || direction == 2) {
			// get the distance from the x position a grid x position
			int key = x % tileSize;
			// if the distance is small/big enough, then it is close to a tile
			if (key < 15 || key > tileSize - 15) {
				// find the target x position to adjust towards
				int tileX = static_cast<int>(x / tileSize)*tileSize;
				int difference = std::abs(x - tileX);
				// if the difference too big, then we took the wrong tile to adjust to
				if (difference > 15) {
					tileX += tileSize;
				}
				// find the coordinates of the target tile
				int tileNumX = tileX / 64;
				int tileNumY = newY / 64;
				tileNumY += direction == 2 ? 1 : 0;
				// get the index of the target tile
				unsigned int target = tileNumY * levelWidth + tileNumX;
				// if the index is valid, check the collision map
				if (target >= 0 || target < collisionMap.size()) {
					// if the target tile is valid, align the x position
					if (collisionMap.at(target) == 0) {
						x = tileX;
						y = newY;
					}
					// otherwise, bring the player to the edge
					else {
						newY = (y / tileSize) * tileSize;
						newY += std::abs(newY - y) > tileSize/2? tileSize : 0;
						y = newY;
					}
				}
			}
			// if the distance isn't small enough, bring the player to the edge
			else {
				newY = (y / tileSize) * tileSize;
				newY += std::abs(newY - y) > tileSize/2 ? tileSize : 0;
				y = newY;
			}
		}else if (direction == 1 || direction == 3) {
			// get the distance from the y position a grid y position
			int key = y % tileSize;
			// if the distance is small/big enough, then it is close to a tile
			if (key < 15 || key > tileSize - 15) {
				// find the target y position to adjust towards
				int tileY = static_cast<int>(y / tileSize)*tileSize;
				int difference = std::abs(y - tileY);
				// if the difference too big, then we took the wrong tile to adjust to
				if (difference > 15) {
					tileY += tileSize;
				}
				// find the coordinates of the target tile
				int tileNumX = newX / 64;
				int tileNumY = tileY / 64;
				tileNumX += direction == 1 ? 1 : 0;
				// get the index of the target tile
				unsigned int target = tileNumY * levelWidth + tileNumX;
				// if the index is valid, check the collision map
				if (target >= 0 || target < collisionMap.size()) {
					// if the target tile is valid, align the y position
					if (collisionMap.at(target) == 0) {
						y = tileY;
					}
					// otherwise, bring the player to the edge
					else {
						newX = (x / tileSize) * tileSize;
						newX += std::abs(newX - x) > tileSize / 2 ? tileSize : 0;
						x = newX;
					}
				}
			}
			// if the distance isn't small enough, bring the player to the edge
			else {
				newX = (x / tileSize) * tileSize;
				newX += std::abs(newX - x) > tileSize / 2 ? tileSize : 0;
				x = newX;
			}
		}
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
	// TODO: optimize collision checking by shrinking checking range
	for (unsigned int i = 0; i < collisionMap.size(); i++) {
		// for now, check every single tile for a collision
		if (collisionMap.at(i) == 1) {	// 1 means it is a collidable tile
			// check the coords of the tile against player position
			int targetX = (i % levelWidth) * tileSize;
			int targetY = static_cast<int>(i / levelWidth) * tileSize;
			// first check x coordinates
			if (xpos + sprite->getTileWidth() > targetX && xpos < (targetX + tileSize)) {
				// check y coordinates
				if (ypos + sprite->getTileHeight() > targetY && ypos < (targetY + tileSize)) {
					// return true only if both x and y intersect
					return true;
				}
			}
		}
	}
	// return false if no collision happened
	return false;
}

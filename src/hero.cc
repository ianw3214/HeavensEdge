#include "hero.h"

#include <iostream>
#include <cmath>

/**
 * Default constructor with initial positions
 */
Hero::Hero(int initX, int initY) : AnimatedSprite("assets/hero.png", 64, 64, 10, false) {
    // TODO: get default variables from input/global variable/something like that
    setAnimationData({1});
    x = initX;
    y = initY;
    health = 5;
    speed = 500;
}

// getter/setter functions
void Hero::setCollisionMap(std::vector<int> inputMap) { collisionMap = inputMap; }
void Hero::setLevelWidth(int width) { levelWidth = width; }
void Hero::setTileSize(int size) { tileSize = size; }

/**
 * Updates the hero
 * @param delta Difference in time between update calls
 */
void Hero::update(float delta){
    AnimatedSprite::update(delta);
}

/**
 * Renders the hero according to camera position
 * @param display SDL_Surface associated with the game window
 * @param camera  SDL_Rect representing the game camera
 */
void Hero::render(SDL_Surface * display, SDL_Rect camera){
    AnimatedSprite::render(display, camera);
}

/**
 * Moves the hero in a certain direction
 * @param direction Integer representation of hero movement direction
 * @param delta     Delta time to account for when calculating move distance
 */
void Hero::move(int direction, float delta){
    // 0 - up, 1 - right, 2 - down, 3 - left
    /*
	if(direction == 0){ 
		y -= speed*delta; 
	}
    if(direction == 1){ 
		x += speed*delta; 
	}
    if(direction == 2){ 
		y += speed*delta; 
	}
    if(direction == 3){ 
		x -= speed*delta; 
	}
	*/
	int units = static_cast<int>(speed*delta);
	for (int i = 0; i < units; i++) {
		int newX = x;
		int newY = y;
		if (direction == 0) { newY--; }
		if (direction == 1) { newX++; }
		if (direction == 2) { newY++; }
		if (direction == 3) { newX--; }
		// if a collision occured, check for a small margin
		if (checkCollision(newX, newY)) {
			// check if the margin is small enough for the player to be adjusted
			if (direction == 0 || direction == 2) {
				int key = x % tileSize;
				std::cout << key << std::endl;
				if (key < 20) {
					int tileX = static_cast<int>(x / tileSize)*tileSize;
					int difference = std::abs(x - tileX);
					// if the difference too big, then we took the wrong tile to adjust to
					if (difference > 20) {
						tileX += tileSize;
					}
					// TODO: Check collision tiles to make sure adjusting only happens when
					//		the player is moving towards non empty tile
					x = tileX;
				}
			}else if (direction == 1 || direction == 3) {
				int key = y % tileSize;
				if (key < 20) {
					int tileY = static_cast<int>(y / tileSize)*tileSize;
					int difference = std::abs(y - tileY);
					// if the difference too big, then we took the wrong tile to adjust to
					if (difference > 20) {
						tileY += tileSize;
					}
					// TODO: Check collision tiles to make sure adjusting only happens when
					//		the player is moving towards non empty tile
					y = tileY;
				}
			}
			// otherwise, don't do anything
		}
		else {
			// otherwise, set the new x and y positions
			x = newX;
			y = newY;
		}
	}
}

/**
 * Checks the hero the see if it collides with a collidable tile
 */
bool Hero::checkCollision(int xpos, int ypos) {
	// TODO: check if player goes out of the map
	// TODO: optimize collision checking by shrinking checking range
	for (int i = 0; i < collisionMap.size(); i++) {
		// for now, check every single tile for a collision
		if (collisionMap.at(i) == 1) {	// 1 means it is a collidable tile
			// check the coords of the tile against player position
			int targetX = (i % levelWidth) * tileSize;
			int targetY = static_cast<int>(i / levelWidth) * tileSize;
			// first check x coordinates
			if (xpos + tileWidth > targetX && xpos < (targetX + tileSize)) {
				// check y coordinates
				if (ypos + tileHeight > targetY && ypos < (targetY + tileSize)) {
					// return true only if both x and y intersect
					return true;
				}
			}
		}
	}
	// return false if no collision happened
	return false;
}
#include "hero.h"

#include <iostream>

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

void Hero::setCollisionMap(std::vector<int> inputMap) { collisionMap = inputMap; }

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
}

/**
* Returns a boolean representing if the player is allowed to move to a certain
* position depending on collision map data
*/
bool Hero::validateMovement(int x, int y) {

}
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
    move(1);
    move(2);
}

/**
 * Updates the hero
 * @param delta Difference in time between update calls
 */
void Hero::update(float delta){
    AnimatedSprite::update(delta);
    // TODO: Let Player class handle movement flags
    // first handle player movement according to movement flags
    if(UP){
        y -= speed*delta;
    }
    if(DOWN){
        y += speed*delta;
    }
    if(LEFT){
        x -= speed*delta;
    }
    if(RIGHT){
        x += speed*delta;
    }
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
 */
void Hero::move(int direction){
    // 0 - up, 1 - right, 2 - down, 3 - left
    if(direction == 0){
        UP = true;
    }
    if(direction == 1){
        RIGHT = true;
    }
    if(direction == 2){
        DOWN = true;
    }
    if(direction == 3){
        LEFT = true;
    }
}

/**
 * Stop hero movement in a certain direction
 * @param direction Integer representation of hero movement direction
 */
void Hero::stopMove(int direction){
    // TODO: remove this function from hero class and let player class handle
    // 0 - up, 1 - right, 2 - down, 3 - left
    if(direction == 0){
        UP = false;
    }
    if(direction == 1){
        RIGHT = false;
    }
    if(direction == 2){
        DOWN = false;
    }
    if(direction == 3){
        LEFT = false;
    }
}

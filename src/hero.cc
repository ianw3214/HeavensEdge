#include "hero.h"

#include <iostream>

// Set up the default hero
Hero::Hero(int initX, int initY) : AnimatedSprite("assets/hero.png", 64, 64, 10, false) {
    // TODO: get default variables from input/global variable/something like that
    setAnimationData({1});
    x = initX;
    y = initY;
    health = 5;
}

void Hero::update(float delta){
    AnimatedSprite::update(delta);
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

void Hero::render(SDL_Surface * display, SDL_Rect camera){
    AnimatedSprite::render(display, camera);
}

// move the hero towards a certain direction
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

// stop the hero movement in a certain direction, opposite of move method
void Hero::stopMove(int direction){
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

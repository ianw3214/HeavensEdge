#include "player.h"

#include <iostream>

Player::Player(){
    hero = new Hero(0, 0);
    upPress = false;
    downPress = false;
    leftPress = false;
    rightPress = false;
}

Player::Player(Hero * initHero){
    hero = initHero;
}

Player::~Player(){
    delete hero;
}

void Player::handleEvents(SDL_Event event){
    if(event.type == SDL_KEYDOWN){
        handleKeyPress(event.key.keysym.sym);
    }else if(event.type == SDL_KEYUP){
        handleKeyRelease(event.key.keysym.sym);
    }
}

void Player::update(float delta){
    hero->update(delta);
	// proccess any key events
	processKeyEvents();
    // handle player movement
	if (moveUp) { hero->move(0, delta); }
	if (moveDown) { hero->move(2, delta); }
	if (moveLeft) { hero->move(3, delta); }
	if (moveRight) { hero->move(1, delta); }
}

void Player::render(SDL_Surface* display, SDL_Rect camera){
    hero->render(display, camera);
}

void Player::handleKeyPress(SDL_Keycode key){
    switch(key){
        case SDLK_UP:{
            upPress = true;
        } break;
        case SDLK_DOWN:{
            downPress = true;
        } break;
        case SDLK_LEFT:{
            leftPress = true;
        } break;
        case SDLK_RIGHT:{
            rightPress= true;
        } break;
    }
}
void Player::handleKeyRelease(SDL_Keycode key){
    switch(key){
        case SDLK_UP:{
            upPress = false;
        } break;
        case SDLK_DOWN:{
            downPress = false;
        } break;
        case SDLK_LEFT:{
            leftPress = false;
        } break;
        case SDLK_RIGHT:{
            rightPress = false;
        } break;
    }
}

/**
 * Processes pressed keys and updates player class accordingly
 */
void Player::processKeyEvents() {
	if (upPress && !downPress && !leftPress && !rightPress) {
		moveUp = true, moveDown = false, moveLeft = false, moveRight =false;
	}
	else if (!upPress && downPress && !leftPress && !rightPress) {
		moveUp = false, moveDown = true, moveLeft = false, moveRight = false;
	}
	else if (!upPress && !downPress && leftPress && !rightPress) {
		moveUp = false, moveDown = false, moveLeft = true, moveRight = false;
	}
	else if (!upPress && !downPress && !leftPress && rightPress) {
		moveUp = false, moveDown = false, moveLeft = false, moveRight = true;
	}
	if (!upPress && !downPress && !rightPress && !leftPress) {
		moveUp = false, moveDown = false, moveLeft = false, moveRight = false;
	}
}
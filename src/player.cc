#include "player.h"

#include <iostream>

Player::Player(){
    hero = new Hero(0, 0);
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
    // handle player movement
    if(UP){ hero->move(0, delta); }
    if(DOWN){ hero->move(2, delta); }
    if(LEFT){ hero->move(3, delta); }
    if(RIGHT){ hero->move(1, delta); }
}

void Player::render(SDL_Surface* display, SDL_Rect camera){
    hero->render(display, camera);
}

void Player::handleKeyPress(SDL_Keycode key){
    switch(key){
        case SDLK_UP:{
            UP = true;
        } break;
        case SDLK_DOWN:{
            DOWN = true;
        } break;
        case SDLK_LEFT:{
            LEFT = true;
        } break;
        case SDLK_RIGHT:{
            RIGHT = true;
        } break;
    }
}
void Player::handleKeyRelease(SDL_Keycode key){
    switch(key){
        case SDLK_UP:{
            UP = false;
        } break;
        case SDLK_DOWN:{
            DOWN = false;
        } break;
        case SDLK_LEFT:{
            LEFT = false;
        } break;
        case SDLK_RIGHT:{
            RIGHT = false;
        } break;
    }
}

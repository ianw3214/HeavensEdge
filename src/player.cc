#include "player.h"

Player::Player(){
    hero = new Hero(0, 0);
}

Player::Player(Hero * initHero){
    hero = initHero;
}

void Player::handleEvents(SDL_Event e){

}

void Player::update(float delta){
    hero->update(delta);
}

void Player::render(SDL_Surface* display, SDL_Rect camera){
    hero->render(display, camera);
}

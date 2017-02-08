#include "state.h"

#include <iostream>
#include <vector>

State::State(){
    // initialize state properties
    nextState = nullptr;
    quit = false;
}

void State::init(){
    test = new Sprite("assets/test.png", 50, 50, 64, 64);
    test2 = new AnimatedSprite("assets/test.png", 64, 64, 3, false);
    AnimatedSprite::animState testi = {0, 2};
    std::vector<AnimatedSprite::animState> tester;
    tester.push_back(testi);
    test2->setAnimationData(tester);
}

void State::exit(){

}

void State::handleEvents(){

}

void State::update(){
    test->update(0.0f);
    test2->update(0.01f);
}

void State::render(SDL_Surface * display){
    test->render(display, {});
    test2->render(display, {});
}

bool State::shouldQuit(){
    return quit;
}

State* State::getNextState(){
    return nextState;
}

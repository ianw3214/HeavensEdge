#include "state.h"

#include <iostream>
#include <vector>

State::State(){
    // initialize state properties
    nextState = nullptr;
    quit = false;
    test = new Map();
}

void State::init(){

}

void State::exit(){

}

void State::handleEvents(){

}

void State::update(){
    test->update();
}

void State::render(SDL_Surface * display){
    SDL_Rect camera = {-32, 0, 1280, 720};
    test->render(display, camera);
}

bool State::shouldQuit(){
    return quit;
}

State* State::getNextState(){
    return nextState;
}

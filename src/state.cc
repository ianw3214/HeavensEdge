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
    test->render(display, {0, 0, 1280, 720});
}

bool State::shouldQuit(){
    return quit;
}

State* State::getNextState(){
    return nextState;
}

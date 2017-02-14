#include "state.h"

#include <iostream>
#include <vector>

State::State(){
    // initialize state properties
    nextState = nullptr;
    quit = false;
}

void State::init(){

}

void State::exit(){

}

void State::handleEvents(){

}

void State::update(float delta){

}

void State::render(SDL_Surface * display){

}

bool State::shouldQuit(){
    return quit;
}

State* State::getNextState(){
    return nextState;
}

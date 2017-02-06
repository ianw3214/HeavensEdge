#include "state.h"

State::State(){
    // initialize state properties
    this->nextState = nullptr;
    this->quit = false;
}

void State::init(){

}

void State::exit(){
    
}

void State::handleEvents(){

}

void State::update(){

}

void State::render(){

}

bool State::shouldQuit(){
    return this->quit;
}

State* State::getNextState(){
    return this->nextState;
}

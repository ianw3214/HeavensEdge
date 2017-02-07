#include "state.h"

State::State(){
    // initialize state properties
    this->nextState = nullptr;
    this->quit = false;
}

void State::init(){
    this->test = new Sprite("assets/test.png", 50, 50, 64, 64);
}

void State::exit(){

}

void State::handleEvents(){

}

void State::update(){
    test->update(0.0f);
}

void State::render(SDL_Surface * display){
    test->render(display, {});
}

bool State::shouldQuit(){
    return this->quit;
}

State* State::getNextState(){
    return this->nextState;
}

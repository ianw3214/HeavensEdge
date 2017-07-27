#include "state.h"

#include <iostream>
#include <vector>

/**
 * Default state constructor
 */
State::State(){
    // set next state to NULL by default
    nextState = nullptr;
    quit = false;
}

/**
 * Default initialization function
 */
void State::init(){

}

/**
 * Default exit function
 */
void State::exit(){

}

/**
 * Default event handler function
 * @param event The event to be handled by the state
 */
void State::handleEvents(SDL_Event event){

}

/**
 * Default update function
 * @param delta The time difference between each update call
 */
void State::update(float delta){

}

/**
 * Default render function
 * @param renderer The SDL renderer to draw the state
 */
void State::render(SDL_Renderer * renderer){

}

/**
 * Getter function for the quit boolean of the state
 * @return A boolean representation of whether the engine should quit the state
 */
bool State::shouldQuit(){
    return quit;
}

/**
 * Getter function for next state
 * @return The state that should be played after the current state
 */
State* State::getNextState(){
    return nextState;
}

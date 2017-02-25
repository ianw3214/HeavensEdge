#include "level.h"

#include <iostream>

// default constructor for levels just for the sake of it
Level::Level(){

}

// load a level and its data from a file
Level::Level(std::string filePath){
    map = new Map("levels/test.txt");
    hero = new Hero(0, 0);
    entities.push_back(hero);
}

/**
 * Initialization function of level
 */
void Level::init(){
    // TODO: initialize camera from NOT hard coded code
    camera = {0, 0, 1280, 720};
}

/**
 * Exit function of level
 */
void Level::exit(){

}

/**
 * Level event handler
 * @param e Event to be processed
 */
void Level::handleEvents(SDL_Event e){

}

/**
 * Updates the level game state
 * @param delta Difference in time between last update call and current
 */
void Level::update(float delta){
    for(int i = 0; i < entities.size(); i++){
        entities.at(i)->update(delta);
    }
}

/**
 * Renders the level
 * @param display The SDL_Surface associated with the game window
 */
void Level::render(SDL_Surface* display){
    map->render(display, camera);
    for(int i = 0; i < entities.size(); i++){
        entities.at(i)->render(display, camera);
    }
}

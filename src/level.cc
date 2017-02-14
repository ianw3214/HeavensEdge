#include "level.h"

#include <iostream>

// default constructor for levels just for the sake of it
Level::Level(){

}

// load a level and its data from a file
Level::Level(std::string filePath){
    map = new Map();
}

void Level::update(float delta){

}

void Level::render(SDL_Surface* display){
    map->render(display, {0, 0, 1280, 720});
}

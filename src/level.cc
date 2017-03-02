#include "level.h"

#include <iostream>

// default constructor for levels just for the sake of it
Level::Level(){

}

// load a level and its data from a file
Level::Level(std::string filePath){
    map = new Map("levels/test.txt");
	// load the collision data to the player
    player = new Player();
	player->setCollisionData(map->getCollisionMap(), map->getWidth(), map->getTileSize());
    entities.push_back(player);
}

/**
 * Initialization function of level
 */
void Level::init(){
    // TODO: initialize camera from NOT hard coded code
    camera.w = 1280;
    camera.h = 720;
}

/**
 * Exit function of level
 */
void Level::exit(){
    delete map;
    delete player;
    for(int i = 0; i < entities.size(); i++){
        delete entities.at(i);
    }
}

/**
 * Level event handler
 * @param e Event to be processed
 */
void Level::handleEvents(SDL_Event e){
    player->handleEvents(e);
}

/**
 * Updates the level game state
 * @param delta Difference in time between last update call and current
 */
void Level::update(float delta){
    // update the map first
    map->update(delta);
	// update the camera position to match the player
	camera.x = player->getCenterX() - camera.w / 2;
	camera.y = player->getCenterY() - camera.h / 2;
	// update each entity in the level
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

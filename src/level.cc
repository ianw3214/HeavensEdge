#include "level.h"

#include <iostream>
#include <cmath>

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
	camSpeed = 2;
	// set initial camera position to player position
	camera.x = player->getCenterX() - camera.w / 2;
	camera.y = player->getCenterY() - camera.h / 2;
}

/**
 * Exit function of level
 */
void Level::exit(){
    delete map;
    delete player;
    for(unsigned int i = 0; i < entities.size(); i++){
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
	updateCamera();
	// update each entity in the level
    for(unsigned int i = 0; i < entities.size(); i++){
        entities.at(i)->update(delta);
    }
}

/**
 * Renders the level
 * @param display The SDL_Surface associated with the game window
 */
void Level::render(SDL_Surface* display){
    map->render(display, camera);
    for(unsigned int i = 0; i < entities.size(); i++){
        entities.at(i)->render(display, camera);
    }
}

/**
 * Moves the camera depending on player position
 */
void Level::updateCamera() {
	// get target camera position
	int targetX = player->getCenterX() - camera.w / 2;
	int targetY = player->getCenterY() - camera.h / 2;
	// update the camera position to match the player
	// if the difference in position is greater than the speed, add the speed to position
	// otherwise, set the position to be equal to target position
	if (std::abs(targetX - camera.x) > camSpeed) {
		if (targetX > camera.x) { camera.x += camSpeed; }
		else { camera.x -= camSpeed; }
	}
	else { camera.x = targetX; }
	if (std::abs(targetY - camera.y) > camSpeed) {
		if (targetY > camera.y) { camera.y += camSpeed; }
		else { camera.y -= camSpeed; }
	}
	else { camera.y = targetY; }
}
#include "level.h"

#include <iostream>
#include <cmath>

// default constructor for levels just for the sake of it
Level::Level(){

}

// load a level and its data from a file
Level::Level(std::string filePath) {
    map = new Map("levels/test.txt");
	// load the collision data to the player
    player = new Player();
	player->setHeroEntities(&entities);
	player->setCollisionData(map->getCollisionMap(), map->getWidth(), map->getTileSize());
    entities.push_back(player);
	// temporarily set new enemies
	Enemy * temp = new Enemy(100, 100);
	Enemy::setCollisionData(map->getCollisionMap(), map->getWidth(), map->getTileSize());
	entities.push_back(temp);
	temp = new Enemy(200, 200);
	entities.push_back(temp);
}

/**
 * Initialization function of level
 */
void Level::init() {
    // TODO: initialize camera from NOT hard coded code
    camera.w = 1280;
    camera.h = 720;
	camSpeed = 2;
	camMargin = 30;
	pause = false;
	player->setPos(map->getStartingX()*map->getTileSize(), map->getStartingY()*map->getTileSize());
	// set initial camera position to player position
	camera.x = player->getCenterX() - camera.w / 2;
	camera.y = player->getCenterY() - camera.h / 2;
}

/**
 * Exit function of level
 */
void Level::exit() {
	delete map;
	// delete all entities in the entities list
    for(int i = entities.size() - 1; i >= 0; i--){
		Entity * temp = entities.at(i);
		entities.erase(entities.begin() + i);
		delete temp;
    }
}

/**
 * Level event handler
 * @param e Event to be processed
 */
void Level::handleEvents(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		handleKeyPress(e.key.keysym.sym);
	}
	player->handleEvents(e);
}

/**
 * Updates the level game state
 * @param delta Difference in time between last update call and current
 */
void Level::update(float delta) {
    // update the game if it is not paused
	if (!pause) {
		// update the map first
		map->update(delta);
		updateCamera();
		// update each entity in the level
		for (unsigned int i = 0; i < entities.size(); i++) {
			entities.at(i)->update(delta);
		}
		// check if the entities should be removed
		for (int i = entities.size() - 1; i >= 0; i--) {
			if (entities.at(i)->getRemove()) {
				Entity * temp = entities.at(i);
				entities.erase(entities.begin() + i);
				delete temp;
			}
		}
	}
}

/**
 * Renders the level
 * @param display The SDL_Surface associated with the game window
 */
void Level::render(SDL_Surface* display) {
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
	if (std::abs(static_cast<double>(targetX - camera.x)) > camMargin) {
		if (targetX > camera.x) { camera.x += camSpeed; }
		else { camera.x -= camSpeed; }
	}
	if (std::abs(static_cast<double>(targetY - camera.y)) > camMargin) {
		if (targetY > camera.y) { camera.y += camSpeed; }
		else { camera.y -= camSpeed; }
	}
}

/**
 * Processes Key down events from the event queue
 * @param key The key that was pressed
 */
void Level::handleKeyPress(SDL_Keycode key) {
	// f key to spawn testing enemies
	if (key == SDLK_f) {
		Enemy * temp = new Enemy(100, 100);
		entities.push_back(temp);
		temp = new Enemy(200, 200);
		entities.push_back(temp);
	}
	// space key to pause the game
	if (key == SDLK_SPACE) {
		pause = !pause;
	}
	// escape key to quit the game
	if (key == SDLK_ESCAPE) {
		nextState = nullptr;
		quit = true;
	}
}
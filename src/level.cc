#include "level.h"

#include <iostream>
#include <cmath>

// default constructor for levels just for the sake of it
Level::Level(){
	Creature::setEntityList(&entities);
	map = new Map("levels/test.txt");
	Creature::setCollisionData(map->getCollisionMap(), map->getWidth(), map->getTileSize());
	// load the collision data to the player
	player = new Player();
	entities.push_back(player);
}

// load a level and its data from a file
Level::Level(std::string filePath) {
	Creature::setEntityList(&entities);
	// load a new player
	player = new Player();
	entities.push_back(player);
	// load the map and its collision data
	map = new Map(filePath);
	Creature::setCollisionData(map->getCollisionMap(), map->getWidth(), map->getTileSize());
}

/**
 * Initialization function of level
 */
void Level::init() {
    // TODO: initialize camera from NOT hard coded code
    camera.w = UTIL::getWindowWidth();
    camera.h = UTIL::getWindowHeight();
	camSpeed = CAMERA_SPEED;
	camMargin = CAMERA_MARGIN;
	pause = false;
	player->setPos(map->getStartingX()*map->getTileSize(), map->getStartingY()*map->getTileSize());
	// set initial camera position to player position
	camera.x = player->getCenterX() - camera.w / 2;
	camera.y = player->getCenterY() - camera.h / 2;
	// load NPCs from map
	for (auto & e : map->getNPCs()) {
		NPC * npc = dynamic_cast<NPC*>(e);
		entities.push_back(npc);
	}
	// load enemies from map
	for (auto & e : map->getEnemies()) {
		Enemy * enemy = dynamic_cast<Enemy*>(e);
		entities.push_back(enemy);
	}
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
		updateCamera(delta);
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
void Level::render(SDL_Renderer* renderer) {
    map->render(renderer, camera);
    for(unsigned int i = 0; i < entities.size(); i++){
        entities.at(i)->render(renderer, camera);
    }
}

/**
 * Moves the camera depending on player position
 */
void Level::updateCamera(float delta) {
	// get target camera position
	int targetX = player->getCenterX() - camera.w / 2;
	int targetY = player->getCenterY() - camera.h / 2;
	// update the camera position to match the player
	// if the difference in position is greater than the speed, add the speed to position
	// otherwise, set the position to be equal to target position
	int xDiff = static_cast<int>(std::abs(static_cast<double>(targetX - camera.x)));
	if (xDiff > camMargin) {
		int speed = camSpeed * delta;
		if (xDiff > WINDOW_WIDTH / 2) speed *= 3;
		if (targetX > camera.x) { camera.x += speed; }
		else { camera.x -= speed; }
	}
	int yDiff = static_cast<int>(std::abs(static_cast<double>(targetY - camera.y)));
	if (yDiff > camMargin) {
		int speed = camSpeed * delta;
		if (yDiff > WINDOW_HEIGHT / 2) speed *= 3;
		if (targetY > camera.y) { camera.y += speed; }
		else { camera.y -= speed; }
	}
}

/**
 * Processes Key down events from the event queue
 * @param key The key that was pressed
 */
void Level::handleKeyPress(SDL_Keycode key) {
	// f key to spawn testing enemies
	if (key == SDLK_f) {
		Enemy * temp = new ChargeEnemy(100, 100);
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
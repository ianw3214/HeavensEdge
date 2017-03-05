#include "player.h"

#include <iostream>

/**
 * Default player constructor
 */
Player::Player(){
	// set the player to a default hero at 0,0
    hero = new Hero(0, 0);
	// TODO: Add variable initialization to an initialization function
    upPress = false;
    downPress = false;
    leftPress = false;
    rightPress = false;
	currentAnimation = IDLE_RIGHT;
}

/**
 * Player constructor with a hero class passed in as the player hero
 * @param initHero The hero that the player is playing
 */
Player::Player(Hero * initHero){
    hero = initHero;
	// TODO: Add variable initialization to an initialization function
	upPress = false;
	downPress = false;
	leftPress = false;
	rightPress = false;
	currentAnimation = IDLE_RIGHT;
}

/**
 * Player destructor
 */
Player::~Player(){
    delete hero;
}

// getter/setter functions
void Player::setCollisionData(std::vector<int> inputMap, int width, int tileSize) {
	hero->setCollisionMap(inputMap);
	hero->setLevelWidth(width);
	hero->setTileSize(tileSize);
}
void Player::setPos(int newX, int newY) {
	hero->setPos(newX, newY);
}
// TODO: change getCenterPos functions to get sprite widths from hero
int Player::getCenterX() const { return hero->getX()+32; }
int Player::getCenterY() const { return hero->getY()+32; }

/**
 * Processes events from the event queue
 * @param event The event to be processed
 */
void Player::handleEvents(SDL_Event event){
	// invoke the helper functions corresponding to the triggered event
    if(event.type == SDL_KEYDOWN){
        handleKeyPress(event.key.keysym.sym);
    }else if(event.type == SDL_KEYUP){
        handleKeyRelease(event.key.keysym.sym);
    }
}

/**
 * Updates the player and it's components
 * @param delta The difference in time between each update calls
 */
void Player::update(float delta){
    hero->update(delta);
	// proccess any key events
	processKeyEvents();
    // handle player movement
	if (moveUp) { hero->move(0, delta); }
	if (moveDown) { hero->move(2, delta); }
	if (moveLeft) { hero->move(3, delta); }
	if (moveRight) { hero->move(1, delta); }
}

/**
 * Renders the player
 * @param display The SDL_Surface associated with the game window
 * @param camera  The SDL_Rect representing the level camera
 */
void Player::render(SDL_Surface* display, SDL_Rect camera){
	// call the hero render function
    hero->render(display, camera);
}

/**
 * Processes Key down events from the event queue
 * @param key The key that was pressed
 */
void Player::handleKeyPress(SDL_Keycode key){
    switch(key){
        case SDLK_UP:{
            upPress = true;
        } break;
        case SDLK_DOWN:{
            downPress = true;
        } break;
        case SDLK_LEFT:{
            leftPress = true;
        } break;
        case SDLK_RIGHT:{
            rightPress= true;
        } break;
    }
}

/**
* Processes Key up events from the event queue
* @param key The key that was released
*/
void Player::handleKeyRelease(SDL_Keycode key){
    switch(key){
        case SDLK_UP:{
            upPress = false;
        } break;
        case SDLK_DOWN:{
            downPress = false;
        } break;
        case SDLK_LEFT:{
            leftPress = false;
        } break;
        case SDLK_RIGHT:{
            rightPress = false;
        } break;
    }
}

/**
 * Processes pressed keys and updates player class accordingly
 */
void Player::processKeyEvents() {
	// TODO: fix bug where pressing 3 keys and then removing 1 causes movement
	//		 to keep going in original direction
	// updates movement flags if only 1 arrow key is pressed
	if (!upPress) { moveUp = false; }
	if (!downPress) { moveDown = false; }
	if (!leftPress) { moveLeft = false; }
	if (!rightPress) { moveRight = false; }
	if (upPress && !downPress && !leftPress && !rightPress) {
		moveUp = true, moveDown = false, moveLeft = false, moveRight =false;
	}
	else if (!upPress && downPress && !leftPress && !rightPress) {
		moveUp = false, moveDown = true, moveLeft = false, moveRight = false;
	}
	else if (!upPress && !downPress && leftPress && !rightPress) {
		moveUp = false, moveDown = false, moveLeft = true, moveRight = false;
	}
	else if (!upPress && !downPress && !leftPress && rightPress) {
		moveUp = false, moveDown = false, moveLeft = false, moveRight = true;
	}
	if (!upPress && !downPress && !rightPress && !leftPress) {
		moveUp = false, moveDown = false, moveLeft = false, moveRight = false;
	}
}

/**
 *	Resets the player animation state to idle in the right direction depending on current state
 */
void Player::setAnimationToIdle() {
	if (moveRight) { currentAnimation = IDLE_RIGHT; }
	else if (moveLeft) { currentAnimation = IDLE_LEFT; }
	else if (moveUp) { currentAnimation = IDLE_UP; }
	else if (moveDown) { currentAnimation = IDLE_DOWN; }
	else { currentAnimation = IDLE_DOWN; }
}
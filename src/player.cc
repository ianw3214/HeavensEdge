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
	faceUp = false;
	faceRight = false;
	faceLeft = false;
	faceDown = false;
	moving = false;
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
	faceUp = false;
	faceRight = false;
	faceLeft = false;
	faceDown = false;
	moving = false;
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
void Player::setHeroEntities(std::vector<GameObject*>* input) { hero->setEntities(input); }
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
	if (moving) {
		// if the direction changed, change the animation
		bool changeDirection = false;
		if (faceUp) {
			hero->move(0, delta);
			if (currentAnimation != MOVE_UP) {
				currentAnimation = MOVE_UP;
				changeDirection = true;
			}
		}
		if (faceDown) {
			hero->move(2, delta);
			if (currentAnimation != MOVE_DOWN) {
				currentAnimation = MOVE_DOWN;
				changeDirection = true;
			}
		}
		if (faceLeft) {
			hero->move(3, delta);
			if (currentAnimation != MOVE_LEFT) {
				currentAnimation = MOVE_LEFT;
				changeDirection = true;
			}
		}
		if (faceRight) {
			hero->move(1, delta);
			if (currentAnimation != MOVE_RIGHT) {
				currentAnimation = MOVE_RIGHT;
				changeDirection = true;
			}
		}
		if (changeDirection) changeAnimation();
	}
	else {
		// if the current animation isn't in idle, change it to idle
		if (currentAnimation > 3) {
			setAnimationToIdle();
		}
	}
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
		case SDLK_x: {
			hero->key1Attack();
		}
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
	// updates movement flags if only 1 arrow key is pressed
	if (upPress && !faceUp) { faceUp = true, faceDown = false, faceLeft = false, faceRight = false; }
	if (downPress && !faceDown) { faceUp = false, faceDown = true, faceLeft = false, faceRight = false; }
	if (leftPress && !faceLeft) { faceUp = false, faceDown = false, faceLeft = true, faceRight = false; }
	if (rightPress && !faceRight) { faceUp = false, faceDown = false, faceLeft = false, faceRight = true; }
	if (upPress || downPress || leftPress || rightPress) { moving = true; }
	else { moving = false; }
}

/**
 *	Resets the player animation state to idle in the right direction depending on current state
 */
void Player::setAnimationToIdle() {
	if (faceRight) {
		currentAnimation = IDLE_RIGHT;
	}
	else if (faceLeft) {
		currentAnimation = IDLE_LEFT;
	}
	else if (faceUp) {
		currentAnimation = IDLE_UP;
	}
	else if (faceDown) {
		currentAnimation = IDLE_DOWN;
	}
	else {
		currentAnimation = IDLE_DOWN;
	}
	changeAnimation();
}

/**
 * Updates the hero to have the current animation of the player
 */
void Player::changeAnimation() {
	hero->playAnimation(currentAnimation);
}
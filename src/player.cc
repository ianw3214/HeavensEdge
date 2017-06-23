#include "player.h"

#include <iostream>

/**
 * Default player constructor
 */
Player::Player(){
	// set the player to a default hero at 0,0
    hero = new Hero(0, 0);
	// TODO: Add variable initialization to an initialization function
	moveUp = false;
	moveDown = false;
	moveRight = false;
	moveLeft = false;
	faceRight = true;
	moving = false;
	currentAnimation = IDLE_RIGHT;
	attackCounter = 0.0;
	attackBar = 0.0;
}

/**
 * Player constructor with a hero class passed in as the player hero
 * @param initHero The hero that the player is playing
 */
Player::Player(Hero * initHero){
    hero = initHero;
	// TODO: Add variable initialization to an initialization function
	moveUp = false;
	moveDown = false;
	moveRight = false;
	moveLeft = false;
	faceRight = true;
	moving = false;
	currentAnimation = IDLE_RIGHT;
	attackCounter = 0.0;
	attackBar = 0.0;
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
void Player::setHeroEntities(std::vector<Entity*>* input) { hero->setEntities(input); }
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
    // handle player movement
	if (!attacking) {
		if (moveUp) {
			hero->move(0, delta);
			moving = true;
		}
		if (moveDown) {
			hero->move(2, delta);
			moving = true;
		}
		if (moveLeft) {
			hero->move(3, delta);
			moving = true;
		}
		if (moveRight) {
			hero->move(1, delta);
			moving = true;
		}
	}
	if (!moveUp && !moveDown && !moveRight && !moveLeft) {
		moving = false;
	}
	if (attackBar != 0.0) {
		if (attackCounter >= attackBar) {
			attackBar = 0.0;
			attackCounter = 0.0;
			attacking = false;
		}
		else {
			attackCounter += delta;
		}
	}
	else {
		// update animations
		if (faceRight && moving) {
			currentAnimation = MOVE_RIGHT;
		}
		else if (!faceRight && moving) {
			currentAnimation = MOVE_LEFT;
		}
		else if (faceRight && !moving) {
			currentAnimation = IDLE_RIGHT;
		}
		else if (!faceRight && !moving) {
			currentAnimation = IDLE_LEFT;
		}
		else {
			currentAnimation = IDLE_RIGHT;
		}
		hero->playAnimation(currentAnimation);
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
            moveUp = true;
        } break;
        case SDLK_DOWN:{
            moveDown = true;
        } break;
        case SDLK_LEFT:{
            moveLeft = true;
			faceRight = false;
        } break;
        case SDLK_RIGHT:{
            moveRight = true;
			faceRight = true;
        } break;
		case SDLK_x: {
			// TODO: Change logic so no continous attacks happen
			key1Attack();
		} break;
		case SDLK_c: {
			key2Attack();
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
            moveUp = false;
        } break;
        case SDLK_DOWN:{
            moveDown= false;
        } break;
        case SDLK_LEFT:{
            moveLeft = false;
			if (moveRight) {
				faceRight = true;
			}
        } break;
        case SDLK_RIGHT:{
            moveRight = false;
			if (moveLeft) {
				faceRight = false;
			}
        } break;
    }
}

/**
 * Updates the hero to have the current animation of the player
 */
void Player::changeAnimation() {
	hero->playAnimation(currentAnimation);
}

/**
 * Handles the attack logic for when the primary attack button is pressed
 */
void Player::key1Attack() {
	if (!attacking) {
		if (faceRight) {
			hero->key1Attack(1);
			currentAnimation = ATTACK1RIGHT;
			hero->setNextAnimation(IDLE_RIGHT);
		}
		else {
			hero->key1Attack(0);
			currentAnimation = ATTACK1LEFT;
			hero->setNextAnimation(IDLE_LEFT);
		}
		changeAnimation();
		attackBar = HERO::ATTACK_1_TIME;
		attackCounter = 0.0;
		attacking = true;
		hero->resetAnimationFrame();
	}
}

/**
 * Handles the attack logic for when the secondary attack button is pressed
 */
void Player::key2Attack() {
	if (!attacking) {
		// attack with a certain direction depending on movement and direction
		if (moveRight) hero->key2Attack(1);
		else if (moveLeft) hero->key2Attack(3);
		else if (moveUp) hero->key2Attack(0);
		else if (moveDown) hero->key2Attack(2);
		else if (faceRight) hero->key2Attack(1);
		else hero->key2Attack(3);
		// set the attack timer
		attackBar = HERO::ATTACK_2_TIME;
		attackCounter = 0.0f;
		attacking = true;
	}
}
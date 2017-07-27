#include "player.h"

#include <iostream>

/**
 * Default player constructor
 */
Player::Player() : Entity(2) {
	// set the player to a default hero at 0,0
    hero = new Hero(0, 0);
	init();
}

/**
 * Player constructor with a hero class passed in as the player hero
 * @param initHero The hero that the player is playing
 */
Player::Player(Hero * initHero) : Entity(2) {
    hero = initHero;
	init();
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
Hero * Player::getHero() const { return hero; }

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
}

/**
 * Renders the player
 * @param display The SDL_Surface associated with the game window
 * @param camera  The SDL_Rect representing the level camera
 */
void Player::render(SDL_Renderer* renderer, SDL_Rect camera){
	// call the hero render function
    hero->render(renderer, camera);
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
			rightPress = true;
        } break;
		case SDLK_x: {
			// TODO: Change logic so no continous attacks happen
			key1Attack();
		} break;
		case SDLK_c: {
			key2Attack();
		} break;
		case SDLK_z: {
			hero->handleDialogue();
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
 * Handles the attack logic for when the primary attack button is pressed
 */
void Player::key1Attack() {
	hero->key1Attack();
}

/**
 * Handles the attack logic for when the secondary attack button is pressed
 */
void Player::key2Attack() {
	hero->key2Attack();
}

void Player::init() {
	// initialize player properties
	hero->syncMoveKeys(&upPress, &rightPress, &downPress, &leftPress);
}
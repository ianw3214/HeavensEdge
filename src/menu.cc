#include "menu.h"

#include <iostream>

/**
 * The default constructor
 *   - Initializes menu items
 */
Menu::Menu() {
	// initialize a test menu
	currentMenuItem = new menuItem(nullptr, nullptr, 1);
	menuItem * item2 = new menuItem(currentMenuItem, nullptr, 2);
	menuItem * item3 = new menuItem(item2, nullptr, 3);
	item2->next = item3;
	currentMenuItem->next = item2;
	// initialize menu background
	background = new Sprite(SPRITE_ID::MENU_BACKGROUND, 0, 0);
	// initialize title
	title = new Sprite(SPRITE_ID::MENU_TITLE, 140, 160, 1000, 200);
	// initialize text sprites
	option1 = new Sprite(SPRITE_ID::MENU_PLAY, 440, 360, 400, 80);
	option2 = new Sprite(SPRITE_ID::MENU_SETTINGS, 440, 440, 400, 80);
	option3 = new Sprite(SPRITE_ID::MENU_QUIT, 440, 520, 400, 80);
	// initialize selection sprite
	selectSprite = new Sprite(SPRITE_ID::MENU_SELECT, 440, 360, 400, 80);
	// initialize other variables
	currentRatioIndex = 0;
}

/**
* Level event handler
* @param event Event to be processed
*/
void Menu::handleEvents(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		handleKeyPress(event.key.keysym.sym);
	}
}

/**
 * Renders the menu to the screen
 * @param display The surface of the game window 
 */
void Menu::render(SDL_Renderer* renderer) {
	background->render(renderer);
	title->render(renderer);
	selectSprite->render(renderer);
	option1->render(renderer);
	option2->render(renderer);
	option3->render(renderer);
}

/**
* Processes Key down events from the event queue
* @param key The key that was pressed
*/
void Menu::handleKeyPress(SDL_Keycode key) {
	if (key == SDLK_SPACE || key == SDLK_RETURN) {
		select();
	}
	if (key == SDLK_DOWN) {
		if (currentMenuItem->next != nullptr) {
			currentMenuItem = currentMenuItem->next;
		}
		std::cout << currentMenuItem->ID;
	}
	if (key == SDLK_UP) {
		if (currentMenuItem->previous != nullptr) {
			currentMenuItem = currentMenuItem->previous;
		}
		std::cout << currentMenuItem->ID;
	}
	if (key == SDLK_ESCAPE) {
		quit = true;
		nextState = nullptr;
	}
	selectSprite->setPos(440, 360 + (currentMenuItem->ID - 1) * 80);
}

/**
 * Handles logic when the player presses the select button
 */
void Menu::select() {
	if (currentMenuItem->ID == 1) {
		nextState = new Level("levels/test.txt");
		quit = true;
	}
	if (currentMenuItem->ID == 2) {
		// switch to the next ratio
		currentRatioIndex++;
		if (currentRatioIndex >= ratios.size()) {
			currentRatioIndex = 0;
		}
		int width = ratios.at(currentRatioIndex).first;
		int height = ratios.at(currentRatioIndex).second;
		// TODO: add options code here
		SDL_SetWindowSize(UTIL::getWindow(), width, height);
		UTIL::setWindowSize(width, height);
	}
	if (currentMenuItem->ID == 3) {
		nextState = nullptr;
		quit = true;
	}
}
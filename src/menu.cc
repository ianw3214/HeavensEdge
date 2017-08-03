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
	background = new Sprite(SPRITE_ID::MENU_BACKGROUND, 0, 0, 1280, 720);
	// initialize title
	title = new Sprite(SPRITE_ID::MENU_TITLE, 140, 260, 1000, 200);
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
}

/**
* Processes Key down events from the event queue
* @param key The key that was pressed
*/
void Menu::handleKeyPress(SDL_Keycode key) {
	if (key == SDLK_SPACE) {
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
		// TODO: add options code here
		SDL_SetWindowSize(UTIL::getWindow(), 720, 480);
		UTIL::setWindowSize(720, 480);
	}
	if (currentMenuItem->ID == 3) {
		nextState = nullptr;
		quit = true;
	}
}
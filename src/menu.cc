#include "menu.h"

#include <iostream>

Menu::Menu() {

}

void Menu::handleEvents(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		handleKeyPress(event.key.keysym.sym);
	}
}

void Menu::handleKeyPress(SDL_Keycode key) {
	if (key == SDLK_SPACE) {
		// go to the level
		nextState = new Level("levels/test.txt");
		quit = true;
	}
}
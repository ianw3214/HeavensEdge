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
	title = new Sprite(SPRITE_ID::MENU_TITLE, 140, 160, TITLE_WIDTH, TITLE_HEIGHT);
	// initialize text sprites
	option1 = new Sprite(SPRITE_ID::MENU_PLAY, 440, 360, OPTION_WIDTH, OPTION_HEIGHT);
	option2 = new Sprite(SPRITE_ID::MENU_SETTINGS, 440, 440, OPTION_WIDTH, OPTION_HEIGHT);
	option3 = new Sprite(SPRITE_ID::MENU_QUIT, 440, 520, OPTION_WIDTH, OPTION_HEIGHT);
	// initialize selection sprite
	selectSprite = new Sprite(SPRITE_ID::MENU_SELECT, 440, 360, OPTION_WIDTH, OPTION_HEIGHT);
	// initialize option overlay sprite
	optionOverlay = new Sprite(SPRITE_ID::OPTION_OVERLAY, 0, 0, 0, 0);
	// initialize other variables
	optionOverlayTweening = false, onOptions = false;
	tweenUp = true;
	tweenStartTime = 0;
	overlayVerticalPosition = 0;
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

void Menu::update(float delta) {
	// update the tween if the sprite is still tweening
	if (optionOverlayTweening) {
		// get the difference in time from the start of the tween to now
		float timeStamp = static_cast<float>(SDL_GetTicks() - tweenStartTime);
		// if the time is over the desired tween time, set the sprite to position 0 and turn flag off
		if (timeStamp >= TWEEN_TIME) {
			overlayVerticalPosition = 0;
			optionOverlayTweening = false;
		}
		// otherwise, update the tween based on the time
		else if (timeStamp != 0) {
			// get the desired function input between 0.5 and 2
			float functionInput = static_cast<float>(timeStamp / TWEEN_TIME) * 1.5f + 0.5f;
			// plug the input into the function to get a number between 0 and 1
			// invert the answer if the tween is downwards
			float functionOutput = 0.0f;
			if (tweenUp) functionOutput = ((1.0f / functionInput) - 0.5f) / 1.5f;
			else functionOutput = 1.0f - ((1.0f / functionInput) - 0.5f) / 1.5f;
			// use the resulting number to calculate the position of the option overlay
			overlayVerticalPosition = static_cast<int>(functionOutput * UTIL::getWindowHeight());
		}
		// set the position of the sprite
		optionOverlay->setPos(0, overlayVerticalPosition);
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
	if (onOptions || optionOverlayTweening) optionOverlay->render(renderer);
}

/**
* Processes Key down events from the event queue
* @param key The key that was pressed
*/
void Menu::handleKeyPress(SDL_Keycode key) {
	if (key == SDLK_SPACE || key == SDLK_RETURN) {
		if (onOptions) {
			// do something
		}
		else {
			select();
		}
	}
	if (key == SDLK_DOWN) {
		if (onOptions) {
			// do something
		}
		else if (currentMenuItem->next != nullptr) {
			currentMenuItem = currentMenuItem->next;
		}
	}
	if (key == SDLK_UP) {
		if (onOptions) {
			// do something
		}
		else if (currentMenuItem->previous != nullptr) {
			currentMenuItem = currentMenuItem->previous;
		}
	}
	if (key == SDLK_ESCAPE) {
		if (onOptions) {
			startTween(false);
			onOptions = false;
		}
		else {
			// go to the last menu item to focus on the quit button
			while (currentMenuItem->next != nullptr) {
				currentMenuItem = currentMenuItem->next;
			}
		}
	}
	selectSprite->setPos(selectSprite->getX(), 360 + (currentMenuItem->ID - 1) * 80);
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
		/*
		// switch to the next ratio
		currentRatioIndex++;
		if (currentRatioIndex >= ratios.size()) {
			currentRatioIndex = 0;
		}
		int width = ratios.at(currentRatioIndex).first;
		int height = ratios.at(currentRatioIndex).second;
		SDL_SetWindowSize(UTIL::getWindow(), width, height);
		UTIL::setWindowSize(width, height);
		// set the sprites to be center
		title->setPos((width - TITLE_WIDTH) / 2, title->getY());
		option1->setPos((width - OPTION_WIDTH) / 2, option1->getY());
		option2->setPos((width - OPTION_WIDTH) / 2, option2->getY());
		option3->setPos((width - OPTION_WIDTH) / 2, option3->getY());
		selectSprite->setPos((width - OPTION_WIDTH) / 2, selectSprite->getY());
		*/
		// start the tween
		startTween(true);
		onOptions = true;
	}
	if (currentMenuItem->ID == 3) {
		nextState = nullptr;
		quit = true;
	}
}

void Menu::startTween(bool up) {
	optionOverlayTweening = true;
	tweenUp = up;
	overlayVerticalPosition = up ? UTIL::getWindowHeight() : 0;
	tweenStartTime = SDL_GetTicks();
	optionOverlay = new Sprite(SPRITE_ID::OPTION_OVERLAY, 0, overlayVerticalPosition, UTIL::getWindowWidth(), UTIL::getWindowHeight());
}
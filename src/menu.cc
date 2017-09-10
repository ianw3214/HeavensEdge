#include "menu.h"

#include <iostream>

/**
 * The default constructor
 *   - Initializes menu items
 */
Menu::Menu() {
	// initialize menu items
	initMenuItems();
	// intialize sprites
	initSprites();
	// initialize settings variables
	currentRatioIndex = 0;
	fullscreen = false;
	currentVolumeIndex = volumes.size() - 1;
	mute = false;
	// initialize other variables
	optionOverlayTweening = false, onOptions = false;
	tweenUp = true;
	tweenStartTime = 0;
	overlayVerticalPosition = 0;
	transitioning = false;
	transitionTimer = 1.0f;
	blackOverlay = new Sprite(SPRITE_ID::BLACK_OVERLAY);
	// start playing menu music
	UTIL::playTrack("assets/music/intro.wav", MUSIC_CHANNEL, true);
}

/**
 * The destructor for the menu class
 */
Menu::~Menu() {
	// delete the menu items starting from the first
	while (currentMenuItem->previous != nullptr)
		currentMenuItem = currentMenuItem->previous;
	while (currentMenuItem->next != nullptr) {
		menuItem * temp = currentMenuItem;
		currentMenuItem = currentMenuItem->next;
		delete temp;
	}
	// delete the option menu items starting from the first
	while (currentOptionMenuItem->previous != nullptr)
		currentOptionMenuItem = currentOptionMenuItem->previous;
	while (currentOptionMenuItem->next != nullptr) {
		menuItem * temp = currentOptionMenuItem;
		currentOptionMenuItem = currentOptionMenuItem->next;
		delete temp;
	}
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
* Updates the menu state
* @param delta The difference in time between each update
*/
void Menu::update(float delta) {
	if (transitioning) {
		transitionTimer -= delta;
		if (transitionTimer <= 0.0f) {
			quit = true;
		}
		else {
			// update the alpha of the overlay if not yet transitioned
			int alpha = static_cast<int>((1.0f - transitionTimer / 1.0f) * 255);
			blackOverlay->setAlpha(alpha);
		}
		return;
	}
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
			float functionInput = 0.0f;
			if (tweenUp) functionInput = static_cast<float>(timeStamp / TWEEN_TIME) * 1.5f + 0.5f;
			else functionInput = (1.0f - static_cast<float>(timeStamp / TWEEN_TIME)) * 1.5f + 0.5f;
			// plug the input into the function to get a number between 0 and 1
			float functionOutput = ((1.0f / functionInput) - 0.5f) / 1.5f;
			// use the resulting number to calculate the position of the option overlay
			overlayVerticalPosition = static_cast<int>(functionOutput * UTIL::getWindowHeight());
		}
		// set the position of the sprite
		optionOverlay->setPos(0, overlayVerticalPosition);
	}
	// update the position of the select cursor for options menu
	int newY = OPTION_SELECT_HEIGHTS[currentOptionMenuItem->ID - 1] + overlayVerticalPosition;
		optionSelectNode->setPos(optionSelectNode->getX(), newY);
}

/**
 * Renders the menu to the screen
 * @param renderer The renderer of the game window
 */
void Menu::render(SDL_Renderer* renderer) {
	background->render(renderer);
	title->render(renderer);
	selectSprite->render(renderer);
	option1->render(renderer);
	option2->render(renderer);
	option3->render(renderer);
	// render the settings menu if player is on options menu
	if (onOptions || optionOverlayTweening) {
		optionOverlay->render(renderer);
		optionSelectNode->render(renderer);
	}
	// render the blakc overlay if transitioning
	if (transitioning) blackOverlay->render(renderer);
}

void Menu::exit() {
	Mix_FadeOutChannel(MUSIC_CHANNEL, 500);
}

/**
* Processes Key down events from the event queue
* @param key The key that was pressed
*/
void Menu::handleKeyPress(SDL_Keycode key) {
	// don't handle any key presses if the menu is already transitioning
	if (transitioning) return;
	if (key == SDLK_SPACE || key == SDLK_RETURN) {
		select();
	}
	if (key == SDLK_DOWN) {
		// play the interact sound
		UTIL::playTrack("assets/sounds/menu.wav", -1, false);
		if (onOptions) {
			if (currentOptionMenuItem->next != nullptr)
				currentOptionMenuItem = currentOptionMenuItem->next;
		}
		else if (currentMenuItem->next != nullptr) {
			currentMenuItem = currentMenuItem->next;
		}
	}
	if (key == SDLK_UP) {
		// play the interact sound
		UTIL::playTrack("assets/sounds/menu.wav", -1, false);
		if (onOptions) {
			if (currentOptionMenuItem->previous != nullptr)
				currentOptionMenuItem = currentOptionMenuItem->previous;
		}
		else if (currentMenuItem->previous != nullptr) {
			currentMenuItem = currentMenuItem->previous;
		}
	}
	if (key == SDLK_ESCAPE) {
		// play the interact sound
		UTIL::playTrack("assets/sounds/menu.wav", -1, false);
		if (onOptions) {
			startTween(false);
			onOptions = false;
		}
		else {
			// if already on last menu item, just quit the game
			if (currentMenuItem->ID == 3) {
				nextState = nullptr;
				quit = true;
			}
			else {
				// go to the last menu item to focus on the quit button
				while (currentMenuItem->next != nullptr) {
					currentMenuItem = currentMenuItem->next;
				}
			}
		}
	}
	selectSprite->setPos(selectSprite->getX(), 360 + (currentMenuItem->ID - 1) * 80);
}

/**
 * Handles logic when the player presses the select button
 */
void Menu::select() {
	// play the settings sound
	UTIL::playTrack("assets/sounds/menu.wav", -1, false);
	// handle the select functionality based on what menu the player is currently on
	if (onOptions) {
		optionSelect();
	}
	else {
		// play the game
		if (currentMenuItem->ID == 1) {
			nextState = new Level("levels/test.txt");
			transitioning = true;
		}
		// open settings menu
		if (currentMenuItem->ID == 2) {
			// start the tween
			startTween(true);
			onOptions = true;
		}
		// quit the game
		if (currentMenuItem->ID == 3) {
			nextState = nullptr;
			transitioning = true;
		}
	}
}

/**
 * Handles the select functionality while on the settings menu
 */
void Menu::optionSelect() {
	// change game window size
	if (currentOptionMenuItem->ID == 1) {
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
	}
	// set game to fullscreen
	if (currentOptionMenuItem->ID == 2) {
		if (!fullscreen) {
			SDL_SetWindowFullscreen(UTIL::getWindow(), SDL_WINDOW_FULLSCREEN);
			fullscreen = true;
		}
		else {
			SDL_SetWindowFullscreen(UTIL::getWindow(), 0);
			fullscreen = false;
		}
	}
	// change game volume
	if (currentOptionMenuItem->ID == 3) {
		if (--currentVolumeIndex < 0) {
			currentVolumeIndex = volumes.size() - 1;
		}
		if (!mute) Mix_Volume(-1, volumes[currentVolumeIndex]);
	}
	// mute the game
	if (currentOptionMenuItem->ID == 4) {
		mute = !mute;
		if (mute) Mix_Volume(-1, 0);
		else Mix_Volume(-1, volumes[currentVolumeIndex]);
	}
	// quit the game
	if (currentOptionMenuItem->ID == 5) {
		startTween(false);
		onOptions = false;
		// go back to the first menu item 
		while (currentOptionMenuItem->previous != nullptr)
			currentOptionMenuItem = currentOptionMenuItem->previous;
	}
}

/**
 * Sets up variables to calculate position during tweens for settings overlay
 * @param up Flag to indicate whether to tween up or tween down
 */
void Menu::startTween(bool up) {
	optionOverlayTweening = true;
	tweenUp = up;
	overlayVerticalPosition = up ? UTIL::getWindowHeight() : 0;
	tweenStartTime = SDL_GetTicks();
	optionOverlay = new Sprite(SPRITE_ID::OPTION_OVERLAY, 0, overlayVerticalPosition, UTIL::getWindowWidth(), UTIL::getWindowHeight());
}

/**
 * Initializes the linked list of menu items and settings menu items
 */
void Menu::initMenuItems() {
	// initialize the menu items
	currentMenuItem = new menuItem(nullptr, nullptr, 1);
	menuItem * item2 = new menuItem(currentMenuItem, nullptr, 2);
	menuItem * item3 = new menuItem(item2, nullptr, 3);
	item2->next = item3;
	currentMenuItem->next = item2;
	// initialize settings menu items
	currentOptionMenuItem = new menuItem(nullptr, nullptr, 1);
	menuItem * optionItem2 = new menuItem(currentOptionMenuItem, nullptr, 2);
	menuItem * optionItem3 = new menuItem(optionItem2, nullptr, 3);
	menuItem * optionItem4 = new menuItem(optionItem3, nullptr, 4);
	menuItem * optionItem5 = new menuItem(optionItem4, nullptr, 5);
	currentOptionMenuItem->next = optionItem2;
	optionItem2->next = optionItem3;
	optionItem3->next = optionItem4;
	optionItem4->next = optionItem5;
}

/**
 * Initializes the sprites used in the menu
 */
void Menu::initSprites() {
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
	// initialize option overlay sprites
	optionOverlay = new Sprite(SPRITE_ID::OPTION_OVERLAY, 0, 0, 0, 0);
	optionSelectNode = new Sprite(SPRITE_ID::OPTION_SELECT, 20, 100, 64, 64);
}
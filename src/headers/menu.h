#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "state.h"
#include "level.h"
#include "sprite.h"
#include "constants.h"

struct menuItem{
	menuItem * previous;
	menuItem * next;
	int ID;
	menuItem(menuItem* a, menuItem* b, int c) : previous(a), next(b), ID(c) {};
};

/**
 * Menu state
 */
class Menu : public State{

public:
	Menu();
	~Menu() {};

	void handleEvents(SDL_Event);
	void update(float);
	void render(SDL_Renderer*);

private:
	menuItem * currentMenuItem;
	Sprite * background;
	Sprite * title;
	Sprite * option1, *option2, *option3;
	Sprite * selectSprite;
	Sprite * optionOverlay;
	Sprite * settingsTitle;

	bool optionOverlayTweening, onOptions;
	bool tweenUp;
	Uint32 tweenStartTime;
	int overlayVerticalPosition;
	int currentRatioIndex;

	void handleKeyPress(SDL_Keycode);
	void select();

	void startTween(bool);

};
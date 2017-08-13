#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "util.h"
#include "state.h"
#include "level.h"
#include "sprite.h"
#include "constants.h"

/**
 * Menu state
 */
class Menu : public State{

public:
	Menu();
	~Menu();

	void handleEvents(SDL_Event);
	void update(float);
	void render(SDL_Renderer*);

private:
	menuItem * currentMenuItem;
	menuItem * currentOptionMenuItem;

	Sprite * background;
	Sprite * title;
	Sprite * option1, *option2, *option3;
	Sprite * selectSprite;
	Sprite * optionOverlay;

	int currentRatioIndex;
	bool fullscreen;
	int currentVolumeIndex;
	bool mute;

	bool optionOverlayTweening, onOptions;
	bool tweenUp;
	Uint32 tweenStartTime;
	int overlayVerticalPosition;

	void handleKeyPress(SDL_Keycode);
	void select();
	void optionSelect();

	void startTween(bool);
	void initMenuItems();
	void initSprites();

};
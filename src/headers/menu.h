#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "state.h"
#include "level.h"

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

private:
	menuItem * currentMenuItem;

	void handleKeyPress(SDL_Keycode);
	void select();

};
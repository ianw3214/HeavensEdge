#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "state.h"
#include "level.h"

class Menu : public State{

public:
	Menu();
	~Menu() {};

	void handleEvents(SDL_Event);

private:
	void handleKeyPress(SDL_Keycode);

};

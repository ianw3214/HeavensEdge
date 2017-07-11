#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "state.h"
#include "tile.h"
#include "constants.h"

#include <ctime>

/**
 * Core engine of the game
 *
 * The engine contains nothing gameplay specific, instead
 * has general functions that call into specific state methods
 * for specific gameplay functionalities.
 */
class Engine{

public:
    Engine(int, int);
    bool init();
	void setState(State*);
    void cleanUp();

	// getter for game window / surface
	SDL_Window* getWindow();
	SDL_Surface* getSurface();

    void handleEvents();
    void update();
    void render();

    bool isRunning();
private:
    int windowWidth, windowHeight;
    bool running;

    State * currentState;

    Uint32 lastTime, currentTime;
    float deltaTime;

    SDL_Window * gWindow;
    SDL_Surface * display;

	int fps, frames;
	float fpsCounter;
	int timePerFrame;
};

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "state.h"

/**
 * Core engine of the game
 *
 * The engine contains nothing gameplay specific, instead
 * has general functions that call into specific state methods
 * for specific gameplay functionalities.
 */
class Engine{

public:
    Engine();
    bool init(State*);
    void cleanUp();

    void handleEvents();
    void update();
    void render();

    bool isRunning();
private:
    bool running;

    State * currentState;

    Uint32 lastTime, currentTime;
    float deltaTime;

    SDL_Window * gWindow;
    SDL_Surface * display;
};

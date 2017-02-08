#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "state.h"

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

    SDL_Window * gWindow;
    SDL_Surface * display;
};

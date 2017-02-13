#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "map.h"

class State{

public:
    State();

    void init();
    void exit();

    void handleEvents();
    void update();
    void render(SDL_Surface*);

    bool shouldQuit();
    State* getNextState();
private:
    Map * test;

    State * nextState;
    bool quit;
};

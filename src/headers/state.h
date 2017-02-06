#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>

class State{

public:
    State();

    void init();
    void exit();

    void handleEvents();
    void update();
    void render();

    bool shouldQuit();
    State* getNextState();
private:
    State * nextState;
    bool quit;
};

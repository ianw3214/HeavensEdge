#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "sprite.h"
#include "animatedSprite.h"

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
    Sprite * test;
    AnimatedSprite * test2;

    State * nextState;
    bool quit;
};

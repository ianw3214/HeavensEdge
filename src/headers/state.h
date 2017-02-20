#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class State{

public:
    State();

    virtual void init();
    virtual void exit();

    virtual void handleEvents(SDL_Event);
    virtual void update(float);
    virtual void render(SDL_Surface*);

    bool shouldQuit();
    State* getNextState();
private:
    State * nextState;
    bool quit;
};

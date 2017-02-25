#pragma once

#include <SDL.h>

/**
 * Base game state used in engine class
 *
 * Contains base virtual methods for the engine to call and
 * child classes to inherit from.
 */
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

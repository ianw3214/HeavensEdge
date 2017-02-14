#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <string>

#include "state.h"
#include "map.h"

class Level : public State{

public:
    Level();
    Level(std::string);

    void init();
    void exit();

    void handleEvents();
    void update(float);
    void render(SDL_Surface*);
private:
    Map * map;
};

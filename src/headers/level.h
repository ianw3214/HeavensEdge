#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <string>
#include <vector>

#include "state.h"
#include "entity.h"
#include "map.h"
#include "hero.h"   // testing

class Level : public State{

public:
    Level();
    Level(std::string);

    void init();
    void exit();

    void handleEvents(SDL_Event);
    void update(float);
    void render(SDL_Surface*);
private:
    Map* map;
    std::vector<Entity*> entities;
    Hero* hero;


    SDL_Rect camera;
};

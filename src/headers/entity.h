#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class Entity{

public:
    virtual void render(SDL_Surface*, SDL_Rect) = 0;
    virtual void update(float) = 0;
};

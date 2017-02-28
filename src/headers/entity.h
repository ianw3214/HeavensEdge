#pragma once

#include <SDL.h>

/**
 * Abstract class providing base functions shared across entities
 */
class Entity{

public:
    virtual void render(SDL_Surface*, SDL_Rect) = 0;
    virtual void update(float) = 0;
};
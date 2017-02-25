#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>

/**
 * Tile class used to form tilemaps
 */
class Tile{
public:
    Tile(std::string, int, int, int, int);

    virtual void update();
    virtual void render(SDL_Surface*, int, int);
protected:
    int tileWidth, tileHeight;

    SDL_Surface * spriteSheet;
    SDL_Rect blitRect;
};

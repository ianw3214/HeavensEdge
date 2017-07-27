#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>

#include "util.h"

/**
 * Tile class used to form tilemaps
 */
class Tile{
public:
    Tile(std::string, int, int, int, int);

    virtual void update(float);
    virtual void render(SDL_Renderer*, int, int);
protected:
    int tileWidth, tileHeight;

	SDL_Texture * tileSheet;
    SDL_Rect blitRect;
};

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

	static void setDisplay(SDL_Surface*);

    virtual void update(float);
    virtual void render(SDL_Surface*, int, int);
protected:
    int tileWidth, tileHeight;

    SDL_Surface * spriteSheet;
    SDL_Rect blitRect;

	static SDL_Surface * screenSurface;
};

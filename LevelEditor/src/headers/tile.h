#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>

/**
 *	Tile class to represent tiles on a map
 */
class Tile {
public:
	Tile(std::string, int, int, int, int);
	~Tile();

	virtual void update(float);
	virtual void render(SDL_Surface*, int, int);
private:
	int tileWidth, tileHeight;

	SDL_Surface * spriteSheet;
	SDL_Rect blitRect;
};
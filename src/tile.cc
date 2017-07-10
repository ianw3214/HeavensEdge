#include "tile.h"

#include <iostream>

// declare static variables
SDL_Surface* Tile::screenSurface;

/**
 * Default tile constructor
 */
Tile::Tile(std::string path, int w, int h, int xPos, int yPos){
    // load the sprite sheet to a temporary surface
    SDL_Surface * tempSurface = IMG_Load(path.c_str());
    if(!tempSurface){
        std::cout << "Image unable to load, error: " << IMG_GetError() << std::endl;
    }
	// optimize the temporary surface and set it to the sprite sheet
	spriteSheet = SDL_ConvertSurface(tempSurface, screenSurface->format, NULL);
	if (spriteSheet == NULL) {
		std::cout << "Unable to optimize image, Error: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(tempSurface);
    // set up the blit Rect of the tile
    blitRect = {xPos*w, yPos*h, w, h};
}

void Tile::setDisplay(SDL_Surface * display) { screenSurface = display; }

/**
 * Base update function for tiles in the tile map
 * @param delta Difference in time between update calls
 */
void Tile::update(float delta){
    // can be changed to include animated tiles in the future
}

/**
 * Renders the tile at a certain position on the screen
 * @param display SDL_Surface associated with the game window
 * @param x       x position of the screen to be rendered on
 * @param y       y position of the screen to be rendered on
 */
void Tile::render(SDL_Surface* display, int x, int y){
    SDL_Rect targetRect = {x, y, 0, 0};
    if(SDL_BlitSurface(spriteSheet, &blitRect, display, &targetRect) < 0){
        std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
    }
}

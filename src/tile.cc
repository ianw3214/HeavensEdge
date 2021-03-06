#include "tile.h"

#include <iostream>

/**
 * Default tile constructor
 */
Tile::Tile(std::string textureID, int w, int h, int xPos, int yPos){
    // load the sprite sheet to a texture
	tileSheet = UTIL::getTextureFromId(textureID);
    // set up the blit Rect of the tile
    blitRect = {xPos*w, yPos*h, w, h};
}

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
void Tile::render(SDL_Renderer * renderer, int x, int y){
    SDL_Rect targetRect = {x, y, 64, 64};
	if (SDL_RenderCopy(renderer, tileSheet, &blitRect, &targetRect) < 0) {
		std::cout << "texture unable to render, error: " << SDL_GetError() << std::endl;
	}
}

#include "tile.h"

#include <iostream>

/**
 * Default tile constructor
 */
Tile::Tile(std::string path, int w, int h, int xPos, int yPos){
    // load the sprite sheet to the tile
    spriteSheet = IMG_Load(path.c_str());
    if(!spriteSheet){
        std::cout << "Image unable to load, error: " << IMG_GetError() << std::endl;
    }
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
void Tile::render(SDL_Surface* display, int x, int y){
    SDL_Rect targetRect = {x, y, 0, 0};
    if(SDL_BlitSurface(spriteSheet, &blitRect, display, &targetRect) < 0){
        std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
    }
}

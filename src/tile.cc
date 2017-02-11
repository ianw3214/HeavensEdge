#include "tile.h"

#include <iostream>

Tile::Tile(std::string path, int w, int h, int xPos, int yPos){
    // load the sprite sheet to the tile
    spriteSheet = IMG_Load(path.c_str());
    if(!spriteSheet){
        std::cout << "Image unable to load, error: " << IMG_GetError() << std::endl;
    }
    // set up the blit Rect of the tile
    blitRect = {xPos*w, yPos*h, w, h};
}

void Tile::update(){
    // base update function for animated tiles
}

void Tile::render(SDL_Surface* display, int x, int y){
    SDL_Rect targetRect = {x, y, 0, 0};
    if(SDL_BlitSurface(spriteSheet, &blitRect, display, &targetRect) < 0){
        std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
    }
}

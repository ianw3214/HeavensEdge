#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <string>

#include "tile.h"

class Map{
public:
    Map();

    void update();
    void render(SDL_Surface*, SDL_Rect);
private:
    int mapWidth, mapHeight;
    int tileWidth, tileHeight;

    std::vector<int> mapData;
};

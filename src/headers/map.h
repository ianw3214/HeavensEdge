#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <string>
#include <map>

#include "tile.h"

class Map{
public:
    Map();

    // TODO: implement loading tile map keys from a file/external class

    void update();
    void render(SDL_Surface*, SDL_Rect);
private:
    int mapWidth, mapHeight;
    int tileWidth, tileHeight;

    std::map<int, Tile*> tileMap;
    std::vector<int> mapData;
};

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
    Map(std::string);

    // TODO: implement loading tile map keys from a file/external class
    bool loadFromFile(std::string);

    void update();
    void render(SDL_Surface*, SDL_Rect);
private:
    int mapWidth, mapHeight;
    int tileWidth, tileHeight;

    std::map<int, Tile*> tileMap;
    std::vector<int> mapData;

    void lineToTileMap(std::string);
    void lineToMapData(std::string);
};

#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <string>
#include <map>

#include "tile.h"

/**
 * Map class representing tile maps
 *
 * Map data is loaded from files
 */
class Map{
public:
    Map();
    Map(std::string);

    bool loadFromFile(std::string);

    void update(float delta);
    void render(SDL_Surface*, SDL_Rect);
private:
    int mapWidth, mapHeight;
    int tileWidth, tileHeight;

    std::map<int, Tile*> tileMap;
    std::vector<int> mapData;

    void lineToTileMap(std::string);
    void lineToMapData(std::string);
};

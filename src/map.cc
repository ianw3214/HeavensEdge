#include "map.h"

#include <iostream>

Map::Map(){
    // Set testing values for now
    // TODO: Modularize map class
    mapData = {0, 0, 0, 0, 1, 0, 0, 0, 0};

    mapWidth = 3;
    mapHeight = 3;
    tileWidth = 64;
    tileHeight = 64;

    // temporarily set the Tile map here
    // TODO: replace with proper initialization code
    Tile * tile1 = new Tile("assets/tiles.png", 64, 64, 0, 0);
    Tile * tile2 = new Tile("assets/tiles.png", 64, 64, 1, 0);
    tileMap[0] = tile2;
    tileMap[1] = tile1;
}

// overload constructor to allow initialization of map stats in constructor
Map::Map(int width, int height, int tWidth, int tHeight){
    mapWidth = width;
    mapHeight = height;
    tileWidth = tWidth;
    tileHeight = tHeight;
}

void Map::update(){
    // update the tiles
}

void Map::render(SDL_Surface * display, SDL_Rect camera){

    // variables used to calculate whether a tile is on screen and should be rendered
    int startX = camera.x;
    int startY = camera.y;
    int endX = camera.x + camera.w;
    int endY = camera.y + camera.h;

    // loop through each tile and render them
    int tileX, tileY;
    for(unsigned int i = 0; i < mapData.size(); i++){
        // calculate the absolute x and y position according to tile position
        tileX = (i % mapWidth)*tileWidth;
        tileY = (static_cast<int>(i/mapWidth))*tileHeight;
        // check to see if tile is on screen
        if(tileX >= startX-tileWidth && tileY >= startY-tileHeight && tileX <= endX && tileY <= endY){
            int key = mapData.at(i);
            if(!(tileMap.find(key) == tileMap.end())){
                tileMap[key]->render(display, tileX - camera.x, tileY - camera.y);
            }
        }
    }
}

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
}

void Map::update(){
    // update the tiles
}

void Map::render(SDL_Surface * display, SDL_Rect camera){
    Tile * tile1 = new Tile("assets/tiles.png", 64, 64, 0, 0);
    Tile * tile2 = new Tile("assets/tiles.png", 64, 64, 1, 0);

    // loop through each tile and render them
    int startX = camera.x;
    int startY = camera.y;
    int endX = camera.x + camera.w;
    int endY = camera.y + camera.h;

    int tileX, tileY;
    for(unsigned int i = 0; i < mapData.size(); i++){
        tileX = (i % 3)*tileWidth;
        tileY = (static_cast<int>(i/3))*tileHeight;
        // check to see if tile is on screen
        if(tileX >= startX-tileWidth && tileY >= startY-tileHeight && tileX <= endX && tileY <= endY){
            std::cout << tileX << " : " << tileY << std::endl;
            if(mapData.at(i) == 0){
                tile1->render(display, tileX, tileY);
            }else{
                tile2->render(display, tileX, tileY);
            }
        }
    }
}

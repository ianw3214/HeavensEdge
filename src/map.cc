#include "map.h"

#include <iostream>
#include <fstream>

Map::Map(){
    // load a default level if no level was specified
    loadFromFile("levels/test.txt");
}

// constructor for loading a map from a file
Map::Map(std::string filePath){
    loadFromFile(filePath);
}

// function to load a level from a file
bool Map::loadFromFile(std::string file){
    std::ifstream fileStream;
    fileStream.open(file);
    std::string line;
    int counter = 0;        // counter to keep track of which line we're reading
    bool onMapData = false;
    while(getline(fileStream, line)){
        // TODO: change conditionals to not depend on order
        if(counter == 0){   // first line is the width of each tile
            int width = std::stoi(line, nullptr);
            tileWidth = width;
        }
        if(counter == 1){   // second line is the height of each tile
            int height = std::stoi(line, nullptr);
            tileHeight = height;
        }
        if(counter == 2){   // third line is the width of each map in tiles
            int width = std::stoi(line, nullptr);
            mapWidth = width;
        }
        if(counter == 3){   // third line is the width of each map in tiles
            int height = std::stoi(line, nullptr);
            mapHeight = height;
        }
        if(onMapData){  // read the numbers into the map data
            lineToMapData(line);
        }
        if(line == "---"){  // stop reading into tile map when token is reached
            onMapData = true;
        }
        if(counter > 3 && !onMapData){  // reading tile info to tileMap
            lineToTileMap(line);
        }
        counter++;
    }
    return true;
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

// Helper function to load tile map data
void Map::lineToTileMap(std::string line){
    // Lines are in the form:
    // index#path#xPosition#yPosition

    // variables to store the final data
    int index, x, y;
    std::string path;

    std::string token = "";     // keep track of what the current token looks like
    int counter = 0;            // keep track of which token we are on
    for(char const & c : line){
        if(c == '#'){
            if(counter == 0){
                // the index of the tile
                index = std::stoi(token, nullptr);
            }
            if(counter == 1){
                // the path of the file
                path = token;
            }
            if(counter == 2){
                // the x position of the tile
                x = std::stoi(token, nullptr);
            }
            token = "";
            counter++;
        }else{
            token += c;
        }
    }
    // after looping, the token should still contain the last y position of the tile
    y = std::stoi(token, nullptr);
    // load all the data into the tilemap
    Tile * newTile = new Tile(path, tileWidth, tileHeight, x, y);
    tileMap[index] = newTile;
    return;
}

// Helper function to load Map data
void Map::lineToMapData(std::string line){
    // each token is seperated by a #

    std::string token = "";

    for(char const & c : line){
        if(c == '#'){
            mapData.push_back(std::stoi(token, nullptr));
            token = "";
        }else{
            token += c;
        }
    }
    mapData.push_back(std::stoi(token, nullptr));
    return;
}

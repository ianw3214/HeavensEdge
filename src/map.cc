#include "map.h"

#include <iostream>
#include <fstream>

/**
 * Default map constructor that loads a default level file
 */
Map::Map(){
    // load a default level if no level was specified
    loadFromFile("levels/test.txt");
}

/**
 * Map constructor that loads a map from a file
 */
Map::Map(std::string filePath){
    loadFromFile(filePath);
}

/**
 * Destructor for map class
 */
Map::~Map(){
	for (std::map<int, Tile*>::iterator itr = tileMap.begin(); itr != tileMap.end(); itr++)
	{
		delete itr->second;
	}
}

// getter/setter functions
std::vector<int> Map::getCollisionMap() const{
	return collisionData;
}
std::vector<NPC*> Map::getNPCs() const {
	return NPCs;
}
std::vector<Enemy*> Map::getEnemies() const {
	return enemies;
}
int Map::getWidth() { return mapWidth; }
int Map::getHeight() { return mapHeight; }
int Map::getTileSize() { return tileWidth; }
int Map::getStartingX() { return startX; }
int Map::getStartingY() { return startY; }

/**
 * Parses data from text file to load map data
 * @param  file Source file to load data from
 * @return      boolean representing the success state of the method
 */
bool Map::loadFromFile(std::string file){
    std::ifstream fileStream;
    fileStream.open(file);
    std::string line;
    int counter = 0;        // counter to keep track of which line we're reading
	/*	0 - MAP DATA
		1 - COLLISION DATA
		2 - NPC DATA
		3 - ENEMY DATA
		
		** starts at -1 to show not on reading specific types of data yet
	*/
	int currentReadingType = -1;
	while (getline(fileStream, line)) {
		// TODO: change conditionals to not depend on order
		if (counter == 0) {   // first line is the width of each tile
			int width = std::stoi(line, nullptr);
			tileWidth = width;
		}
		if (counter == 1) {   // second line is the height of each tile
			int height = std::stoi(line, nullptr);
			tileHeight = height;
		}
		if (counter == 2) {   // third line is the width of each map in tiles
			int width = std::stoi(line, nullptr);
			mapWidth = width;
		}
		if (counter == 3) {   // third line is the width of each map in tiles
			int height = std::stoi(line, nullptr);
			mapHeight = height;
		}
		if (counter == 4) {		// the starting x position of the player
			startX = std::stoi(line);
		}
		if (counter == 5) {		// the starting y position of the player
			startY = std::stoi(line);
		}
		if (currentReadingType == 3) { // read the line to enemy data
			lineToEnemy(line);
		}
		if (line == "%%%") {	// stop reading into NPC data when token is reached
			currentReadingType = 3;
		}
		if (currentReadingType == 2) {	// read the line into NPC data
			lineToNPCData(line);
		}
		if (line == "+++") {	// stop reading into collision data when token is reached
			currentReadingType = 2;
		}
		if (currentReadingType == 1) {	// read the numbers into the collision data
			lineToCollisionData(line);
		}
		if (line == "***") {	// stop reading into map data when token is reached
			currentReadingType = 1;
		}
		if (currentReadingType == 0) {  // read the numbers into the map data
			lineToMapData(line);
		}
		if (line == "---") {  // stop reading into tile map when token is reached
			currentReadingType = 0;
		}
		if (counter > 5 && currentReadingType < 0) {
			// reading tile info to tileMap
			lineToTileMap(line);
		}
		counter++;
	}
    return true;
}

/**
 * Updates the map
 * @param delta Difference in time between update calls
 */
void Map::update(float delta) {
    for(auto const& tile : tileMap) {
        tile.second->update(delta);
    }
}

/**
 * Renders the map according to camera position
 * @param display SDL_Surface associated with the game window
 * @param camera  SDL_Rect representing the game camera
 */
void Map::render(SDL_Surface * display, SDL_Rect camera) {
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

/**
 * Helper function to laod file data to tileMap data
 * @param line Input line from the file
 */
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

/**
 * Helper function to load file data to map data
 * @param line The line to be parsed
 */
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

/**
* Helper function to load file data to collision data
* @param line The line to be parsed
*/
void Map::lineToCollisionData(std::string line) {
	// each token is seperated by a #

	std::string token = "";

	for (char const & c : line) {
		if (c == '#') {
			int key = std::stoi(token, nullptr);
			if (key == 0) { collisionData.push_back(0); }
			else { collisionData.push_back(1); }
			token = "";
		}
		else {
			token += c;
		}
	}
	collisionData.push_back(std::stoi(token, nullptr));
	return;
}

/**
* Helper function to load file data to NPC data
* @param line The line to be parsed
*/
void Map::lineToNPCData(std::string line) {

	std::string token = "";
	int counter = 0;
	// variables to hold the NPC data
	NPC * thisNPC = nullptr;
	int x, y;
	std::vector<std::string> dialogue;
	std::string path;

	for (char const & c : line) {
		if (c == '#') {
			if (counter == 0) {
				x = std::stoi(token, nullptr);
				x *= 64;
			}
			if (counter == 1) {
				y = std::stoi(token, nullptr);
				y *= 64;
			}
			if (counter == 2) {
				path = token;
			}
			if (counter >= 3) {
				dialogue.push_back(token);
			}
			// reset the token and increment the counter
			token = "";
			counter++;
		}
		else {
			token += c;
		}
	}

	// if the counter >= 3, then we missed one last token
	if (counter >= 3) dialogue.push_back(token);

	thisNPC = new NPC(x, y, dialogue, path);
	NPCs.push_back(thisNPC);

	return;
}

/**
* Helper function to load file data to enemy data
* @param line The line to be parsed
*/
void Map::lineToEnemy(std::string line) {

	std::string token = "";
	int counter = 0;
	// variables to hold the NPC data
	Enemy * thisEnemy = nullptr;
	int x, y;

	for (char const & c : line) {
		if (c == '#') {
			if (counter == 0) {
				x = std::stoi(token, nullptr);
				x *= 64;
			}
			if (counter == 1) {
				y = std::stoi(token, nullptr);
				y *= 64;
			}
			// reset the token and increment the counter
			token = "";
			counter++;
		}
		else {
			token += c;
		}
	}
	// determine the type of enemy depending on the last token
	int ID = std::stoi(token, nullptr);
	if (ID == 0) enemies.push_back(new Enemy(x, y));
	if (ID == 1) enemies.push_back(new ChargeEnemy(x, y));

	return;

}
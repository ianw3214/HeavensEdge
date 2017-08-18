#include "map.h"

Map::Map() {
	init();
	initTileIndexMap();
}

Map::~Map()
{
}

std::map<int, Tile*> Map::getIndexMap() { return indexMap; }
void Map::setSettings(int tw, int th, int mw, int mh, int sx, int sy) {
	tileWidth = tw, tileHeight = th;
	mapWidth = mw, mapHeight = mh;
	startX = sx, startY = sy;
}
void Map::setPlayerCoords(int _x, int _y) { startX = _x, startY = _y; }
void Map::setEmptyMap() {
	for (int i = 0; i < mapHeight * mapWidth; i++) {
		tileMap.push_back(0);
		collisionMap.push_back(0);
	}
}
int Map::getPlayerX() { return startX; }
int Map::getPlayerY() { return startY; }

void Map::update() {
	// eventually do something here I guess
}

void Map::render(SDL_Surface* display, int x, int y) {
	for (unsigned int i = 0; i < tileMap.size(); i++) {
		int tileX = (i % BASE_MAP_WIDTH) * TILE_WIDTH;
		int tileY = (i / BASE_MAP_WIDTH) * TILE_HEIGHT;
		int key = tileMap.at(i);
		if (!(indexMap.find(key) == indexMap.end())) {
			indexMap[key]->render(display, tileX + x, tileY + y);
		}
	}
}

void Map::renderCollisionTiles(SDL_Surface* display, int x, int y) {
	for (unsigned int i = 0; i < collisionMap.size(); i++) {
		int tileX = (i % BASE_MAP_WIDTH) * TILE_WIDTH;
		int tileY = (i / BASE_MAP_WIDTH) * TILE_HEIGHT;
		int key = collisionMap.at(i);
		SDL_Rect targetRect = { tileX + x, tileY + y, 0, 0 };
		if (key == 1){
			if (SDL_BlitSurface(collisionImage, nullptr, display, &targetRect) < 0) {
				std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
			}
		}
	}
}

void Map::editTileAt(int x, int y, int index) {
	// make sure the input position is within the map
	if (x < 0 || y < 0 || x > BASE_MAP_WIDTH * TILE_WIDTH || y > BASE_MAP_HEIGHT * TILE_HEIGHT) {
		return;
	}
	// make sure the target index is within the index map
	if (index < 0 || index > indexMap.size()) {
		return;
	}
	int xTile = static_cast<int>(x / 64);
	int yTile = static_cast<int>(y / 64);
	int target = yTile * BASE_MAP_WIDTH + xTile;
	tileMap[target] = index;
	return;
}

void Map::editCollision(int x, int y, bool add) {
	// make sure the input position is within the map
	if (x < 0 || y < 0 || x > BASE_MAP_WIDTH * TILE_WIDTH || y > BASE_MAP_HEIGHT * TILE_HEIGHT) {
		return;
	}
	int xTile = static_cast<int>(x / 64);
	int yTile = static_cast<int>(y / 64);
	int target = yTile * BASE_MAP_WIDTH + xTile;
	collisionMap[target] = add ? 1 : 0;
	return;
}

void Map::loadFromFile(std::string path) {
	std::ifstream fileStream;
	fileStream.open(path);
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
		// break out of the while loop when reading NPC data because it is not needed
		if (currentReadingType > 2) {
			break;
		}
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
		if (line == "%%%") {	// stop reading into NPC data when token is reached
			currentReadingType = 3;
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
			// lineToTileMap(line);
			// don't read tilesheet data because that is set in the editor settings
		}
		counter++;
	}
}

void Map::saveToFile() {
	std::ofstream target;
	target.open(OUTPUT_FILE_PATH);
	target << tileWidth << "\n";
	target << tileHeight << "\n";
	target << mapWidth << "\n";
	target << mapHeight << "\n";
	target << startX<< "\n";
	target << startY << "\n";
	// add all of the tile indices
	// first calculate the width and height of the input image used to calculate the position of each index
	SDL_Surface* tileSheet = IMG_Load(TILE_SHEET_FILE_PATH.c_str());
	int width = tileSheet->w / TILE_WIDTH;
	for ( auto const &i : indexMap) {
		int x = i.first % width;
		int y = static_cast<int>(i.first / width);
		target << i.first << "#" << TILE_SHEET_ID << "#" << x << "#" << y << "\n";
	}
	target << "---\n";	
	for (int i = 0; i < BASE_MAP_HEIGHT; i++) {
		for (int j = 0; j < BASE_MAP_WIDTH; j++) {
			target << tileMap[i * BASE_MAP_WIDTH + j];
			if (j == BASE_MAP_WIDTH - 1) target << "\n";
			else target << "#";
		}
	}
	target << "***\n";
	for (int i = 0; i < BASE_MAP_HEIGHT; i++) {
		for (int j = 0; j < BASE_MAP_WIDTH; j++) {
			target << collisionMap[i * BASE_MAP_WIDTH + j];
			if (j == BASE_MAP_WIDTH - 1) target << "\n";
			else target << "#";
		}
	}
	target.close();
	std::cout << "MAP SAVED TO: " << OUTPUT_FILE_PATH << std::endl;
}

void Map::init() {
	tileSheetPath = TILE_SHEET_FILE_PATH;
	// load the image for the collision mode tiles
	collisionImage = IMG_Load(COLLISION_TILE_FILE_PATH.c_str());
	if (!collisionImage) std::cout << "Could not load image: assets/collision.png, ERROR: " << IMG_GetError() << std::endl;
	// set all variables to 0
	tileWidth = 0, tileHeight = 0;
	mapWidth = 0, mapHeight = 0;
	startX = 0, startY = 0;
}

void Map::initTileIndexMap() {
	// calculate the width and height of the input image
	SDL_Surface* tileSheet = IMG_Load(TILE_SHEET_FILE_PATH.c_str());
	int width = tileSheet->w / TILE_WIDTH, height = tileSheet->h / TILE_HEIGHT;
	// loop through all tiles in the input image
	int numTiles = width * height;
	for (int i = 0; i < numTiles; i++) {
		// calculate the x and y coordinate of the tile
		int x = i % width, y = static_cast<int>(i / width);
		Tile * newTile = new Tile(TILE_SHEET_FILE_PATH, TILE_WIDTH, TILE_HEIGHT, x, y);
		indexMap[i] = newTile;
	}
	return;
}

void Map::lineToCollisionData(std::string line) {
	// each token is seperated by a #

	std::string token = "";

	for (char const & c : line) {
		if (c == '#') {
			int key = std::stoi(token, nullptr);
			if (key == 0) { collisionMap.push_back(0); }
			else { collisionMap.push_back(1); }
			token = "";
		}
		else {
			token += c;
		}
	}
	collisionMap.push_back(std::stoi(token, nullptr));
	return;
}

void Map::lineToMapData(std::string line) {
	// each token is seperated by a #

	std::string token = "";

	for (char const & c : line) {
		if (c == '#') {
			tileMap.push_back(std::stoi(token, nullptr));
			token = "";
		}
		else {
			token += c;
		}
	}
	tileMap.push_back(std::stoi(token, nullptr));
	return;
}
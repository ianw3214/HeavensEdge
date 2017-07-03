#include "map.h"

Map::Map() {
	init();
	initTileIndexMap();
}

Map::~Map()
{
}

void Map::update() {

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

void Map::saveToFile() {

}

void Map::init() {
	for (int i = 0; i < BASE_MAP_HEIGHT * BASE_MAP_WIDTH; i++) {
		tileMap.push_back(0);
		collisionMap.push_back(0);
	}

	tileSheetPath = TILE_SHEET_FILE_PATH;
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
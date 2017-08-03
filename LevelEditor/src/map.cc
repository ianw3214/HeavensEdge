#include "map.h"

Map::Map() {
	init();
	initTileIndexMap();
}

Map::~Map()
{
}

std::map<int, Tile*> Map::getIndexMap() { return indexMap; }

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

void Map::saveToFile(int playerX, int playerY) {
	std::ofstream target;
	target.open(OUTPUT_FILE_PATH);
	std::cout << "FLAG" << std::endl;
	target << TILE_WIDTH << "\n";
	target << TILE_HEIGHT << "\n";
	target << BASE_MAP_WIDTH << "\n";
	target << BASE_MAP_HEIGHT << "\n";
	target << playerX << "\n";
	target << playerY << "\n";
	// add all of the tile indices
	// first calculate the width and height of the input image used to calculate the position of each index
	SDL_Surface* tileSheet = IMG_Load(TILE_SHEET_FILE_PATH.c_str());
	int width = tileSheet->w / TILE_WIDTH;
	for ( auto const &i : indexMap) {
		int x = i.first % width;
		int y = static_cast<int>(i.first / width);
		target << i.first << "#" << TILE_SHEET_FILE_PATH << "#" << x << "#" << y << "\n";
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
}

void Map::init() {
	for (int i = 0; i < BASE_MAP_HEIGHT * BASE_MAP_WIDTH; i++) {
		tileMap.push_back(0);
		collisionMap.push_back(0);
	}

	tileSheetPath = TILE_SHEET_FILE_PATH;
	// load the image for the collision mode tiles
	collisionImage = IMG_Load(COLLISION_TILE_FILE_PATH.c_str());
	if (!collisionImage) std::cout << "Could not load image: assets/collision.png, ERROR: " << IMG_GetError() << std::endl;
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
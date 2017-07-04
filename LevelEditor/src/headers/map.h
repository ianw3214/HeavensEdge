#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>
#include <map>

#include "tile.h"
#include "constants.h"

class Map {
public:
	Map();
	~Map();

	// getter/setters
	std::map<int, Tile*> getIndexMap();

	void update();
	void render(SDL_Surface*, int, int);

	void saveToFile();
private:
	std::vector<int> tileMap;
	std::vector<int> collisionMap;

	std::map<int, Tile*> indexMap;
	std::string tileSheetPath;

	void init();
	void initTileIndexMap();
};
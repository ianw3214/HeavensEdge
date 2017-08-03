#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

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

	void renderCollisionTiles(SDL_Surface*, int, int);

	void editTileAt(int, int, int);
	void editCollision(int, int, bool);

	void saveToFile(int, int);
private:
	std::vector<int> tileMap;
	std::vector<int> collisionMap;

	std::map<int, Tile*> indexMap;
	std::string tileSheetPath;

	void init();
	void initTileIndexMap();

	SDL_Surface * collisionImage;
};
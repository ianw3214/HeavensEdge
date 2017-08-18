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
	void setSettings(int, int, int, int, int, int);
	void setPlayerCoords(int, int);
	void setEmptyMap();
	int getPlayerX();
	int getPlayerY();

	void update();
	void render(SDL_Surface*, int, int);

	void renderCollisionTiles(SDL_Surface*, int, int);

	void editTileAt(int, int, int);
	void editCollision(int, int, bool);

	void loadFromFile(std::string);
	void saveToFile();
private:
	std::vector<int> tileMap;
	std::vector<int> collisionMap;

	std::map<int, Tile*> indexMap;
	std::string tileSheetPath;

	void init();
	void initTileIndexMap();

	int tileWidth, tileHeight;
	int mapWidth, mapHeight;
	int startX, startY;
	SDL_Surface * collisionImage;

	void lineToCollisionData(std::string);
	void lineToMapData(std::string);
};
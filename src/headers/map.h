#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <string>
#include <map>

#include "constants.h"
#include "tile.h"
#include "entity.h"
#include "npc.h"

/**
 * Map class representing tile maps
 *
 * Map data is loaded from files
 */
class Map : public Entity{
public:
    Map();
    Map(std::string);
    ~Map();

    bool loadFromFile(std::string);

	// getter/setter functions
	std::vector<int> getCollisionMap() const;
	std::vector<NPC*> getNPCs() const;
	int getWidth();
	int getHeight();
	int getTileSize();
	int getStartingX();
	int getStartingY();

    void update(float delta);
    void render(SDL_Surface*, SDL_Rect);
private:
    int mapWidth, mapHeight;
    int tileWidth, tileHeight;
	int startX, startY;		// the starting position of the player

    std::map<int, Tile*> tileMap;
    std::vector<int> mapData;
	std::vector<int> collisionData;
	std::vector<NPC*> NPCs;

    void lineToTileMap(std::string);
    void lineToMapData(std::string);
	void lineToCollisionData(std::string);
	void lineToNPCData(std::string);
};

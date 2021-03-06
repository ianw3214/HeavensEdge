#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <string>
#include <map>

#include "util.h"
#include "constants.h"
#include "tile.h"
#include "entity.h"

#include "npc.h"
#include "enemy.h"
#include "chargeEnemy.h"
#include "boss.h"

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
	std::vector<Enemy*> getEnemies() const;
	std::map<Rectangle*, std::string> getTransitionTiles() const;
	int getWidth();
	int getHeight();
	int getTileSize();
	int getStartingX();
	int getStartingY();

    void update(float delta);
    void render(SDL_Renderer*, SDL_Rect);
private:
    int mapWidth, mapHeight;
    int tileWidth, tileHeight;
	int startX, startY;		// the starting position of the player

    std::map<int, Tile*> tileMap;
    std::vector<int> mapData;
	std::vector<int> collisionData;
	std::vector<NPC*> NPCs;
	std::vector<Enemy*> enemies;
	std::map<Rectangle*, std::string> transitionTiles;

    void lineToTileMap(std::string);
    void lineToMapData(std::string);
	void lineToCollisionData(std::string);
	void lineToNPCData(std::string);
	void lineToEnemy(std::string);
	void lineToChangeMapTile(std::string);
};

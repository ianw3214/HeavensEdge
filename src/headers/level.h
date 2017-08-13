#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <string>
#include <vector>

#include "sprite.h"
#include "state.h"
#include "menu.h"
#include "entity.h"
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "chargeEnemy.h"
#include "npc.h"

#include "constants.h"
#include "util.h"

/**
 * Level game state
 */
class Level : public State{

public:
    Level();
    Level(std::string);

    void init();
    void exit();

    void handleEvents(SDL_Event);
    void update(float);
    void render(SDL_Renderer*);
private:
    Map* map;
    std::vector<Entity*> entities;
    Player* player;

	Sprite * deathMenuBackground;
	menuItem * currentDeathMenuItem;

	int camSpeed;
	int camMargin;

    SDL_Rect camera;
	void updateCamera(float);
	void handleKeyPress(SDL_Keycode);

	bool pause;
	bool gameOver;

	void select();
};

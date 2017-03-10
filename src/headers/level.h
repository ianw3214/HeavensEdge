#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <string>
#include <vector>

#include "state.h"
#include "gameObject.h"
#include "map.h"
#include "player.h"
#include "enemy.h"

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
    void render(SDL_Surface*);
private:
    Map* map;
    std::vector<GameObject*> entities;
    Player* player;

	int camSpeed;
	int camMargin;

    SDL_Rect camera;
	void updateCamera();
};

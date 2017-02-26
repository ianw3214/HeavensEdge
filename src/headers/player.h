#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "hero.h"
#include "entity.h"

/**
 * Player controller class that controls heros
 */
class Player : public Entity{

public:
    Player();
    Player(Hero*);

    void handleEvents(SDL_Event);
    void update(float);
    void render(SDL_Surface*, SDL_Rect);
private:
    Hero * hero;

    bool UP, DOWN, LEFT, RIGHT;

    void handleKeyPress(SDL_Keycode);
    void handleKeyRelease(SDL_Keycode);
};

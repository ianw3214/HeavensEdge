#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "animatedSprite.h"

/**
 * Base hero class representing entities controllable by the player
 */
class Hero : public AnimatedSprite{

public:
    Hero(int, int);

    void update(float);
    void render(SDL_Surface*, SDL_Rect);

    void move(int, float);
    void stopMove(int);
protected:
    int health;
    int speed;
};

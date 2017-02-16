#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "animatedSprite.h"

class Hero : public AnimatedSprite{

public:
    Hero(int, int);

    void update(float);
    void render(SDL_Surface*, SDL_Rect);

    void move(int);
    void stopMove(int);
protected:
    int x, y;
    int health;
    int speed;

    bool UP, DOWN, LEFT, RIGHT;
};

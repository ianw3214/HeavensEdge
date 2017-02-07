#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>
#include <string>

class Sprite{

public:
    Sprite(std::string);
    Sprite(std::string, int, int);
    Sprite(std::string, int, int, int, int);

    virtual int getX() const;
    virtual int getY() const;
    virtual void setPos(int, int);
    virtual SDL_Rect getCollisionRect() const;
    virtual void setCollisionWidth(int);
    virtual void setCollisionHeight(int);
    virtual void setCollisionRect(int, int);

    virtual void update(float);
    virtual void render(SDL_Surface*, SDL_Rect);
private:
    int x, y;
    int collisionWidth, collisionHeight;

    SDL_Rect collisionRect;

    SDL_Surface * img;

    bool REMOVE;

    void init(int x, int y, int w, int h);
    void loadImage(std::string);
};

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <string>

#include "gameObject.h"

/**
 * Base sprite class
 *
 * All entities in the game that have a visual representation
 * should be children of the sprite class
 */
class Sprite : public GameObject{

public:
    Sprite(std::string);
    Sprite(std::string, int, int);
    Sprite(std::string, int, int, int, int);
	virtual ~Sprite() {};

    // getter/setter functions
    virtual int getX() const;
    virtual int getY() const;
    virtual void setPos(int, int);
    virtual SDL_Rect getCollisionRect() const;
    virtual void setCollisionWidth(int);
    virtual void setCollisionHeight(int);
    virtual void setCollisionRect(int, int);
    virtual void changeSpriteSheet(std::string);

    void update(float);
    void render(SDL_Surface*, SDL_Rect);
protected:
    SDL_Surface* img;

    int x, y;
    int collisionWidth, collisionHeight;
    SDL_Rect collisionRect;
private:
    void init(int x, int y, int w, int h);
    void loadImage(std::string);
};

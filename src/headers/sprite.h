#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>

#include "entity.h"

/**
 * Base sprite class
 *
 * All entities in the game that have a visual representation
 * should be children of the sprite class
 */
class Sprite : public Entity{

public:

    Sprite(std::string);
    Sprite(std::string, int, int);
    Sprite(std::string, int, int, int, int);
	virtual ~Sprite() {};

    // getter/setter functions
    virtual int getX() const;
    virtual int getY() const;
    virtual void setPos(int, int);
    virtual void changeSpriteSheet(std::string);

    void update(float);
	void render(SDL_Surface*);
    void render(SDL_Surface*, SDL_Rect);
protected:
    SDL_Surface* img;

    int x, y;
	int w, h;

private:
    void init(int x, int y, int w, int h);
    void loadImage(std::string);
};

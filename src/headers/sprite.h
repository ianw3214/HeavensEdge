#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>

#include "entity.h"
#include "util.h"

/**
 * Base sprite class
 *
 * All entities in the game that have a visual representation
 * should be children of the sprite class
 */
class Sprite : public Entity{

public:

    Sprite(std::string, SDL_Renderer*);
    Sprite(std::string, int, int, SDL_Renderer*);
    Sprite(std::string, int, int, int, int, SDL_Renderer*);
	virtual ~Sprite() {};

    // getter/setter functions
    virtual int getX() const;
    virtual int getY() const;
    virtual void setPos(int, int);
    virtual void changeSpriteSheet(std::string, SDL_Renderer*);

    void update(float);
	void render(SDL_Renderer*);
    void render(SDL_Renderer*, SDL_Rect);
protected:
	SDL_Texture * texture;

    int x, y;
	int w, h;

private:
    void init(int x, int y, int w, int h);
};

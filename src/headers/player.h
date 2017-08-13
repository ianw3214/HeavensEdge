#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>

#include "hero.h"
#include "entity.h"

/**
 * Player controller class that controls heros
 */
class Player : public Entity{

public:
    Player();
    Player(Hero*);
    ~Player();

	// getter/setter functions
	void setCollisionData(std::vector<int>, int, int);
	void setPos(int, int);
	int getCenterX() const;
	int getCenterY() const;
	int getHealth() const;
	Hero * getHero() const;

    void handleEvents(SDL_Event);
    void update(float);
    void render(SDL_Renderer*, SDL_Rect);
private:

    Hero * hero;

	bool upPress, rightPress, downPress, leftPress;

    void handleKeyPress(SDL_Keycode);
    void handleKeyRelease(SDL_Keycode);

	void key1Attack();
	void key2Attack();

	void init();
};

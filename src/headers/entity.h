#pragma once

#include <SDL.h>

/**
 * Abstract class providing base functions shared across entities.
 *   - Every object in the game is represented by a base entity class.
 */
class Entity {

public:
	Entity();
	Entity(int);
	
	int getType() const;
	bool getRemove() const;

	static void setDisplay(SDL_Surface*);

	virtual void handleEvents(SDL_Event) {};
	virtual void update(float) = 0;
	virtual void render(SDL_Surface*, SDL_Rect) = 0;

protected:
	/* Integer representation of entity type:
	  - 1: General
	  - 2: Player
	  - 3: Enemy 
	*/
	int type;
	/* Boolean flag to show if the entity should be removed. */
	bool REMOVE;

	void init(int);

	static SDL_Surface * screenDisplay;
};

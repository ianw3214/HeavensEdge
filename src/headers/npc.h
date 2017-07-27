#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "creature.h"

#include <vector>
#include <iostream>
#include <string>

class NPC : public Creature{

public:

	NPC(SDL_Renderer*);
	NPC(int, int, SDL_Renderer*);
	NPC(int, int, std::vector<std::string>, SDL_Renderer*);
	NPC(int, int, std::vector<std::string>, std::string, SDL_Renderer*);
	virtual ~NPC() {}

	// getter/setter methods
	std::vector<std::string> getDialogue() const;

	void update(float);
	void render(SDL_Renderer*, SDL_Rect);

private:

	void init(std::string, SDL_Renderer*);
	std::vector<std::string> dialogue;

};
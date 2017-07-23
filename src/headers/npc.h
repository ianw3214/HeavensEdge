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

	NPC();
	NPC(int, int);
	NPC(int, int, std::vector<std::string>);
	NPC(int, int, std::vector<std::string>, std::string);
	virtual ~NPC() {}

	// getter/setter methods
	std::vector<std::string> getDialogue() const;

	void update(float);
	void render(SDL_Surface*, SDL_Rect);

private:

	void init(std::string);
	std::vector<std::string> dialogue;

};
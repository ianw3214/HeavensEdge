#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

#include "collision.h"
#include "constants.h"

struct menuItem {
	menuItem * previous;
	menuItem * next;
	int ID;
	menuItem(menuItem* a, menuItem* b, int c) : previous(a), next(b), ID(c) {};
};

class UTIL {
public:
	// initialization functions to be called in the engine
	static void loadTextures(SDL_Renderer*);
	static SDL_Texture * loadTexture(std::string, SDL_Renderer*);

	static SDL_Texture * getTextureFromId(std::string);

	static void setWindow(SDL_Window*);
	static SDL_Window* getWindow();

	static void setWindowSize(int, int);
	static int getWindowWidth();
	static int getWindowHeight();
private:
	static std::map<std::string, SDL_Texture*> textureMap;
	static SDL_Window* gameWindow;
	static int screenWidth, screenHeight;
};
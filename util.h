#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

#include "constants.h"

class UTIL {
public:
	// initialization functions to be called in the engine
	static void loadTextures(SDL_Renderer*);
	static SDL_Texture * loadTexture(std::string, SDL_Renderer*);

	static SDL_Texture * getTextureFromId(std::string);

	static void setWindow(SDL_Window*);
	static SDL_Window* getWindow();
private:
	static std::map<std::string, SDL_Texture*> textureMap;
	static SDL_Window* gameWindow;
};
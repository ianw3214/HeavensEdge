#pragma once

#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

namespace UTIL {
	SDL_Texture * loadTexture(std::string, SDL_Renderer*);
}
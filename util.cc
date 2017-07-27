#include "util.h"


SDL_Texture* UTIL::loadTexture(std::string path, SDL_Renderer * renderer) {
	// the final texture to return
	SDL_Texture * texture = NULL;

	// load the image onto a surface first
	SDL_Surface * loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) std::cout << "Unable to load image: " << path << ", ERROR: " << IMG_GetError() << std::endl;
	else {
		// create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL) std::cout << "Unable to create texture: " << path << ", ERROR: " << SDL_GetError() << std::endl;
		// get rid of the loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return texture;
}
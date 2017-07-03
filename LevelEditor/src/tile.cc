#include "tile.h"

Tile::Tile(std::string path, int w, int h, int xPos, int yPos) {
	spriteSheet = IMG_Load(path.c_str());
	if (!spriteSheet) {
		std::cout << "Image unable to load, error: " << IMG_GetError() << std::endl;
	}
	blitRect = {xPos * w, yPos * h, w, h};
}

Tile::~Tile()
{
	SDL_FreeSurface(spriteSheet);
}

void Tile::update(float delta) {
	// does not do anything at the moment, can be changed to make animations
}

void Tile::render(SDL_Surface* display, int x, int y) {
	SDL_Rect targetRect = {x, y, 0, 0 };
	if (SDL_BlitSurface(spriteSheet, &blitRect, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
	}
}
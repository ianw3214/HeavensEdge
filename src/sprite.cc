#include "sprite.h"

#include <iostream>

// Sprite constructor with just an image path
Sprite::Sprite(std::string textureID){
	texture = UTIL::getTextureFromId(textureID);
    init(0, 0, 0, 0);
}

// Sprite constructor with position and image path
Sprite::Sprite(std::string textureID, int x, int y){
	texture = UTIL::getTextureFromId(textureID);
    init(x, y, 0, 0);
}

// sprite constructor with position, image path, and collision info
Sprite::Sprite(std::string textureID, int x, int y, int w, int h){
	texture = UTIL::getTextureFromId(textureID);
    init(x, y, w, h);
}

// getter/setter methods
int Sprite::getX() const{ return x; }
int Sprite::getY() const{ return y; }
void Sprite::setPos(int newX, int newY){ x=newX, y=newY; }
void Sprite::changeSpriteSheet(std::string path, SDL_Renderer* renderer) { 
	texture = UTIL::loadTexture(path, renderer); 
}

/**
 * Updates sprite
 * @param delta Difference in time between each update call
 */
void Sprite::update(float delta){
    // sprites don't do anything upon update by default
}

/**
* Renders sprite according to a default camera position
* @param display SDL_Surface associated with the game window
*/
void Sprite::render(SDL_Renderer* renderer) {
	if (SDL_RenderCopy(renderer, texture, nullptr, nullptr) < 0) {
		std::cout << "Sprite unable to render, error: " << SDL_GetError() << std::endl;
	}
}

/**
 * Renders sprite according to camera position
 * @param display SDL_Surface associated with the game window
 * @param camera  SDL_Rect representing the game camera
 */
void Sprite::render(SDL_Renderer* renderer, SDL_Rect camera){
    SDL_Rect targetRect = {x - camera.x, y - camera.y, w, h};
    if(SDL_RenderCopy(renderer, texture, nullptr, &targetRect) < 0){
        std::cout << "Sprite unable to render, error: " << SDL_GetError() << std::endl;
	}
}

/**
 * Sprite initialization function
 * @param _x initial x position of sprite
 * @param _y initial y position of sprite
 * @param _w width of sprite
 * @param _h height of sprite
 */
void Sprite::init(int _x, int _y, int _w, int _h){
    // intialize default variables
    x = _x;
    y = _y;
	w = _w;
	h = _h;
}
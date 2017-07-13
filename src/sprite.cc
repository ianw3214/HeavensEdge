#include "sprite.h"

#include <iostream>

// Sprite constructor with just an image path
Sprite::Sprite(std::string path){
    loadImage(path);
    init(0, 0, 0, 0);
}

// Sprite constructor with position and image path
Sprite::Sprite(std::string path, int x, int y){
    loadImage(path);
    init(x, y, 0, 0);
}

// sprite constructor with position, image path, and collision info
Sprite::Sprite(std::string path, int x, int y, int w, int h){
    loadImage(path);
    init(x, y, w, h);
}

// getter/setter methods
int Sprite::getX() const{ return x; }
int Sprite::getY() const{ return y; }
void Sprite::setPos(int newX, int newY){ x=newX, y=newY; }
void Sprite::changeSpriteSheet(std::string path){ loadImage(path); }

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
void Sprite::render(SDL_Surface * display) {
	if (SDL_BlitSurface(img, nullptr, display, nullptr) < 0) {
		std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
	}
}

/**
 * Renders sprite according to camera position
 * @param display SDL_Surface associated with the game window
 * @param camera  SDL_Rect representing the game camera
 */
void Sprite::render(SDL_Surface * display, SDL_Rect camera){
    SDL_Rect targetRect = {x - camera.x, y - camera.y, 0, 0};
    if(SDL_BlitSurface(img, nullptr, display, &targetRect) < 0){
        std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
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

/**
 * load the sprite sheet from specified path to the sprite
 * @param path Path to desired sprite image
 */
void Sprite::loadImage(std::string path){
	// load the image to a temporary surface first to optimize later
    img = IMG_Load(path.c_str());
    if(!img){
        std::cout << "Image loading failed: " << path << ", error: " << IMG_GetError() << std::endl;
    }
}

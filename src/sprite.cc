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
SDL_Rect Sprite::getCollisionRect() const{ return collisionRect; }
void Sprite::setPos(int newX, int newY){ x=newX, y=newY; }
void Sprite::setCollisionWidth(int w){ collisionWidth = w; }
void Sprite::setCollisionHeight(int h){ collisionHeight = h; }
void Sprite::setCollisionRect(int x, int y){ collisionRect.x = x; collisionRect.y = y; }
void Sprite::changeSpriteSheet(std::string path){ loadImage(path); }

/**
 * Updates sprite
 * @param delta Difference in time between each update call
 */
void Sprite::update(float delta){
    // Set the collision Rects to match new positions
    collisionRect.x = x;
    collisionRect.y = y;
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
    collisionWidth = _w;
    collisionHeight = _h;
    collisionRect = {_x, _y, _w, _h};
    REMOVE = false;
}

/**
 * load the sprite sheet from specified path to the sprite
 * @param path Path to desired sprite image
 */
void Sprite::loadImage(std::string path){
    img = IMG_Load(path.c_str());
    if(!img){
        std::cout << "Image loading failed: " << path << ", error: " << IMG_GetError() << std::endl;
    }
}

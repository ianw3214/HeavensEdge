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

// sprite render function
void Sprite::update(float delta){
    // sprites do nothing by default
}

// sprite render function that renders according to camera position
void Sprite::render(SDL_Surface * display, SDL_Rect camera){
    SDL_Rect targetRect = {x - camera.x, y - camera.y, 0, 0};
    if(SDL_BlitSurface(img, nullptr, display, &targetRect) < 0){
        std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
    }
}

void Sprite::init(int _x, int _y, int _w, int _h){
    // intialize default variables
    x = _x;
    y = _y;
    collisionWidth = _w;
    collisionHeight = _h;
    collisionRect = {_x, _y, _w, _h};
    REMOVE = false;
}

// load the sprite sheet from specified path to the sprite
void Sprite::loadImage(std::string path){
    img = IMG_Load(path.c_str());
    if(!img){
        std::cout << "Image loading failed: " << path << ", error: " << IMG_GetError() << std::endl;
    }
}

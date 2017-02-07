#include "sprite.h"

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
int Sprite::getX() const{ return this->x; }
int Sprite::getY() const{ return this->y; }
SDL_Rect Sprite::getCollisionRect() const{ return this->collisionRect; }
void Sprite::setPos(int x, int y){ this->x=x, this->y=y; }
void Sprite::setCollisionWidth(int w){ this->collisionWidth = w; }
void Sprite::setCollisionHeight(int h){ this->collisionHeight = h; }
void Sprite::setCollisionRect(int x, int y){ this->collisionRect.x = x; this->collisionRect.y = y; }

// sprite render function
void Sprite::update(float delta){
    // sprites do nothing by default
    std::cout << this->collisionWidth << " : " << this->collisionRect.w << std::endl;
}

// sprite render function that renders according to camera position
void Sprite::render(SDL_Surface * display, SDL_Rect camera){
    SDL_Rect targetRect = {x - camera.x, y - camera.y, 0, 0};
    if(SDL_BlitSurface(img, nullptr, display, &targetRect) < 0){
        std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
    }
}

void Sprite::init(int x, int y, int w, int h){
    // intialize default variables
    this->x = x;
    this->y = y;
    this->collisionWidth = w;
    this->collisionHeight = h;
    this->collisionRect = {x, y, w, h};
    this->REMOVE = false;
}

// load the sprite sheet from specified path to the sprite
void Sprite::loadImage(std::string path){
    this->img = IMG_Load(path.c_str());
    if(!img){
        std::cout << "Image loading failed: " << path << ", error: " << IMG_GetError() << std::endl;
    }
}

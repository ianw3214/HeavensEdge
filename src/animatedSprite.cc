#include "animatedSprite.h"

#include <iostream>

AnimatedSprite::AnimatedSprite(std::string path, int w, int h, int ssw, bool shouldPlayOnce=false) : Sprite(path){
    tileWidth = w;
    tileHeight = h;
    collisionRect.w = w;
    collisionRect.h = h;
    spriteSheetWidth = ssw;
    currentFrame = 0;
    deltaTime = 0.0f;
    playOnce = shouldPlayOnce;
}

// set the animation data of the sprite
void AnimatedSprite::setAnimationData(std::vector<int> inputData){
    animData = inputData;
    currentAnim = 0;
}

// update the animated sprite frames
void AnimatedSprite::update(float delta){
    deltaTime += delta;
    // TODO: customize update frame rate
    if(deltaTime >= 0.33f){
        currentFrame++;
        if(currentFrame >= animData.at(currentAnim)){
            if(playOnce) REMOVE = true;
            currentFrame = 0;
        }
        deltaTime = 0.0f;
        updateBlitRect();
    }
}

// render according to the current blit position
void AnimatedSprite::render(SDL_Surface* display, SDL_Rect camera){
    SDL_Rect targetRect = {x-camera.x, y-camera.y, 0, 0};
    if(SDL_BlitSurface(img, &blitRect, display, &targetRect) < 0){
        std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
    }
}

void AnimatedSprite::updateBlitRect(){
    std::cout << currentFrame << std::endl;
    int xPos = currentFrame % spriteSheetWidth;
    // round down for y position divided by sprite sheet width
    int yPos = static_cast<int>(currentFrame/spriteSheetWidth);
    blitRect = {tileWidth * xPos, tileHeight * yPos, tileWidth, tileHeight};
}

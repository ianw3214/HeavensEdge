#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>

#include "sprite.h"

class AnimatedSprite : public Sprite{

public:

    AnimatedSprite(std::string, int, int, int, bool);
    void setAnimationData(std::vector<int>);

    // TODO: method to change playing animation

    virtual void update(float);
    virtual void render(SDL_Surface*, SDL_Rect);

private:
    int tileWidth, tileHeight;
    int spriteSheetWidth;
    int currentFrame;
    SDL_Rect blitRect;

    float deltaTime;

    std::vector<int> animData;
    int currentAnim;

    bool playOnce;

    void updateBlitRect();
};

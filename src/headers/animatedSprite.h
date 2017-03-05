#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>

#include "sprite.h"

/**
 * Base animated sprite class
 *
 * Uses sprite sheets to play animations
 */
class AnimatedSprite : public Sprite{

public:

    AnimatedSprite(std::string, int, int, int, bool);
    void setAnimationData(std::vector<int>);

	void playAnimation(int);

    virtual void update(float);
    virtual void render(SDL_Surface*, SDL_Rect);

protected:
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

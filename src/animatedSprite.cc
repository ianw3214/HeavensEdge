#include "animatedSprite.h"

#include <iostream>

/**
 * Constructor of AnimatedSprite class
 */
AnimatedSprite::AnimatedSprite(std::string textureID, int _w, int _h, int ssw, bool shouldPlayOnce=false) : Sprite(textureID){
    tileWidth = _w;
    tileHeight = _h;
	w = _w;
	h = _h;
    spriteSheetWidth = ssw;
    currentFrame = 0;
    deltaTime = 0.0f;
    playOnce = shouldPlayOnce;
}

/**
 * Sets the animation data of the sprite
 * @param inputData Vector representation of how many frames are in each animation state(row in sprite sheet) of the sprite
 */
void AnimatedSprite::setAnimationData(std::vector<int> inputData){
    animData = inputData;
    currentAnim = 0;
	nextAnim = -1;
}

// getter/setter for tile width/height
int AnimatedSprite::getTileWidth() const { return tileWidth; }
int AnimatedSprite::getTileHeight() const { return tileHeight; }

/**
 * Plays the animation associated with the row of the vector/spritesheet
 * @param row The row of animation to play
 */
void AnimatedSprite::playAnimation(int row) {
	currentAnim = row;
}

void AnimatedSprite::setNextAnimation(int anim) {
	nextAnim = anim;
}

void AnimatedSprite::resetAnimationFrame() {
	currentFrame = 0;
}

/**
 * Updates the animated sprite
 * @param delta Difference in time between each update call
 */
void AnimatedSprite::update(float delta){
	Sprite::update(delta);
    deltaTime += delta;
    // TODO: customize update frame rate
    // Updates the animation frame if desired time has passed
    if(deltaTime >= 0.03f){
        currentFrame++;
        // resets animation if end is reached
        if(currentFrame >= animData.at(currentAnim)){
            // remove the animation if it should only be played once
			if (playOnce) {	REMOVE = true; }
            currentFrame = 0;
			// reset the animation to the queued animation if specified
			if (nextAnim >= 0) {
				currentAnim = nextAnim;
				nextAnim = -1;
			}
        }
        // reset the delta time once frame has been incremented
        deltaTime = 0.0f;
        // update the blitting rect of the sprite sheet to match animation frame
        updateBlitRect();
    }
}

/**
 * Renders the animated sprite according to camera position
 * @param display SDL_Surface associated with the game window
 * @param camera  SDL_Rect representing the game camera
 */
void AnimatedSprite::render(SDL_Renderer* renderer, SDL_Rect camera){
    SDL_Rect targetRect = {x-camera.x, y-camera.y, w, h};
	if (SDL_RenderCopy(renderer, texture, &blitRect, &targetRect) < 0) {
		std::cout << "Sprite unable to render, error: " << SDL_GetError() << std::endl;
	}
}

/**
 * Updates the blitting rect of the sprite sheet according to current animation
 * state and animation frame
 */
void AnimatedSprite::updateBlitRect(){
    int xPos = currentFrame % spriteSheetWidth;
    // round down for y position divided by sprite sheet width
	int yPos = currentAnim;
    blitRect = {tileWidth * xPos, tileHeight * yPos, tileWidth, tileHeight};
}

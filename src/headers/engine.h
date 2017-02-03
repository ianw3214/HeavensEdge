#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>

class Engine{

public:
    Engine();
    bool init();
    void cleanUp();

    void handleEvents();
    void update();
    void render();

    bool isRunning();
private:
    bool running;

    SDL_Window * gWindow;
    SDL_Surface * display;
};

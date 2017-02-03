#include "engine.h"

Engine::Engine(){

}

bool Engine::init(){
    // initialize SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }else{
        // create a game window
        gWindow = SDL_CreateWindow("Heaven's Edge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
        if(gWindow == nullptr){
            std::cout << "Window initialization failed: " << SDL_GetError() << std::endl;
            return false;
        }
        display = SDL_GetWindowSurface(gWindow);
        // initialize image loading library
        int success = IMG_Init(IMG_INIT_PNG);
        if(success&IMG_INIT_PNG != IMG_INIT_PNG){
            std::cout << "Image initialization failed: " << IMG_GetError() << std::endl;
            return false;
        }
        // initialize audio library
        if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0){
            std::cout << "Audio initialization failed: " << Mix_GetError() << std::endl;
            return false;
        }
    }
    this->running = true;
    return true;
}

void Engine::cleanUp(){
    // clean up SDL resources
}

void Engine::handleEvents(){
    // temporary code to escape window when escape key pressed or window quit
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            running = false;
        }
    }
}

void Engine::update(){

}

void Engine::render(){

}

bool Engine::isRunning(){
    return this->running;
}

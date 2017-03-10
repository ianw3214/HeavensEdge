#include "engine.h"

#include <iostream>

/**
 * Engine constructor
 * @param width  The width of the game window
 * @param height The height of the game window
 */
Engine::Engine(int width, int height){
    windowWidth = width;
    windowHeight = height;
}

/**
 * Initializes the game engine by initializing SDL subsystems
 * @param  initialState The first state to be played upon engine creation
 * @return              returns whether initialization was successful
 */
bool Engine::init(State* initialState){

    // initialize SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }else{
        // create a game window
        gWindow = SDL_CreateWindow("Heaven's Edge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        if(gWindow == nullptr){
            std::cout << "Window initialization failed: " << SDL_GetError() << std::endl;
            return false;
        }
        // set display surface to the one associated with game window
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
    // set intiial state of game engine
    this->currentState = initialState;
    this->currentState->init();
    this->running = true;
    return true;
}

/**
 * Cleans up SDL subsystems
 */
void Engine::cleanUp(){
	// free allocated memory
	delete currentState;

    // Destroy the window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	// quit SDL_mixer
	Mix_CloseAudio();

	// Quit SDL subsystems
	SDL_Quit();
}

/**
 * Polls for events and passes them into the state event handlers
 */
void Engine::handleEvents(){
    // temporary code to escape window when escape key pressed or window quit
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            running = false;
        }
        this->currentState->handleEvents(e);
    }
}

/**
 * Updates the game state and calculates time difference between each call
 */
void Engine::update(){
    currentTime = SDL_GetTicks();
    deltaTime = static_cast<float>(currentTime - lastTime)/1000.0;
    lastTime = currentTime;
    currentState->update(deltaTime);
    // check to see if the state should be changed
    if(currentState->shouldQuit()){
        currentState->exit();
        State * nextState = currentState->getNextState();
        // if there is a next state, change it to be the current state
        if(nextState){
            currentState = nextState;
            currentState->init();
        }else{
            // if there is no next state, exit the game
            running = false;
        }
    }
}

/**
 * Resets the window and calls the state render function
 */
void Engine::render(){
    // Fill the window black before updating the WINDOW
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0, 0, 0));
    this->currentState->render(display);
    SDL_UpdateWindowSurface(gWindow);
}

/**
 * Returns whether the game is still running
 * @return A boolean value representing the running state of the game
 */
bool Engine::isRunning(){
    return this->running;
}

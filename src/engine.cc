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
bool Engine::init(){
	// initialize random seed
	srand(time(nullptr));

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
        // initialize a renderer based on the window
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL) {
			std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
		else {
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		}
        // initialize image loading library
        int success = IMG_Init(IMG_INIT_PNG);
        if((success & IMG_INIT_PNG) != IMG_INIT_PNG){
            std::cout << "Image initialization failed: " << IMG_GetError() << std::endl;
            return false;
        }
        // initialize audio library
        if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0){
            std::cout << "Audio initialization failed: " << Mix_GetError() << std::endl;
            return false;
        }
    }
	// load all the textures
	UTIL::loadTextures(gRenderer);
	// initialize variables
	fps = 0, frames = 0;
	fpsCounter = 0.0f;
	timePerFrame = static_cast<int>(1000 / FRAME_RATE_CAP);
	this->running = true;
	// temporarily load settings from constants.h
	if(MUTE) Mix_Volume(-1, 0);
    return true;
}

void Engine::setState(State* state) {
	// set intiial state of game engine
	this->currentState = state;
	this->currentState->init();
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
	// calculate the deltaTime
    currentTime = SDL_GetTicks();
    deltaTime = static_cast<float>(currentTime - lastTime)/1000.0f;
    lastTime = currentTime;
	// handle events before each update
	handleEvents();
	// call the update function of the state
    currentState->update(deltaTime);
	// render the state after each update
	render();
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
	if (fpsCounter > 1.0f) {
		fps = frames;
		std::cout << "FPS: " << fps << std::endl;
		frames = 0;
		fpsCounter = 0.0f;
	}
	else {
		fpsCounter += deltaTime;
		frames++;
	}
	// get the time to see if frame rate needs to be capped
	int tempTime = SDL_GetTicks();
	int difference = tempTime - lastTime;
	// if the difference in time is too small, delay the next update
	if (difference < timePerFrame) {
		SDL_Delay(timePerFrame - difference);
	}
}

/**
 * Resets the window and calls the state render function
 */
void Engine::render(){
    // Fill the window black before updating the WINDOW
	SDL_RenderClear(gRenderer);
	// render the current state
    this->currentState->render(gRenderer);
	// update the screen
	SDL_RenderPresent(gRenderer);
}

/**
 * Returns whether the game is still running
 * @return A boolean value representing the running state of the game
 */
bool Engine::isRunning(){
    return this->running;
}

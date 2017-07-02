#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

// global variables
SDL_Window * gWindow;
SDL_Surface * display;
bool running;

// function declarations
bool init();
void cleanUp();

void handleEvents();
void update();
void render();

int main(int argc, char* argv[]) {

	std::cout << "hello world" << std::endl;
	init();

	while (running) {
		handleEvents();
		update();
		render();
	}

	cleanUp();

	std::cin.get();

	return 0;

}

bool init() {
	// initialize SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}
	else {
		// create a game window
		gWindow = SDL_CreateWindow("Heaven's Edge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr) {
			std::cout << "Window initialization failed: " << SDL_GetError() << std::endl;
			return false;
		}
		// set display surface to the one associated with game window
		display = SDL_GetWindowSurface(gWindow);
		// initialize image loading library
		int success = IMG_Init(IMG_INIT_PNG);
		if ((success & IMG_INIT_PNG) != IMG_INIT_PNG) {
			std::cout << "Image initialization failed: " << IMG_GetError() << std::endl;
			return false;
		}
	}
	// initialize variables
	running = true;
}

void cleanUp() {
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_Quit();
}

void handleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			running = false;
		}
	}
}

void update() {

}

void render() {
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0, 0, 0));
	SDL_UpdateWindowSurface(gWindow);
}
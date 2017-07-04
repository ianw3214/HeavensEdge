#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <map>

#include "map.h"

// custom data structures
struct tileNode {
	tileNode(Tile* iTile, tileNode* iPrev, tileNode* iNext, int iIndex) : tile(iTile), previous(iPrev), next(iNext), index(iIndex) {}
	Tile * tile;
	tileNode * next;
	tileNode * previous;
	int index;
	int xPos;
};

// global variables
SDL_Window * gWindow;
SDL_Surface * display;
bool running;

Map *map;
int xOffset, yOffset;
int xMouseStartPos, yMouseStartPos;
int xOffsetStart, yOffsetStart;

bool SPACE, LMB;

tileNode * currentTile;

// function declarations
bool init();
void cleanUp();

void handleEvents();
void update();
void render();

void setTileLinkedList();
void renderTileLinkedList();

int main(int argc, char* argv[]) {

	init();

	map = new Map();

	setTileLinkedList();

	while (running) {
		handleEvents();
		update();
		render();
	}

	cleanUp();

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
	xOffset = 0, yOffset = 0;
	xMouseStartPos = 0, yMouseStartPos = 0;
	xOffsetStart = 0, yOffsetStart = 0;
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
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
			if (e.key.keysym.sym == SDLK_SPACE) {
				SPACE = true;
			}
		}
		if (e.type == SDL_KEYUP) {
			if (e.key.keysym.sym == SDLK_SPACE) {
				SPACE = false;
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				LMB = true;
				// set the starting mouse position to move map
				SDL_GetMouseState(&xMouseStartPos, &yMouseStartPos);
				xOffsetStart = xOffset, yOffsetStart = yOffset;
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				LMB = false;
			}
		}
	}
}

void update() {
	map->update();
	if (SPACE && LMB) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		int xMouseDiff = mouseX - xMouseStartPos;
		int yMouseDiff = mouseY - yMouseStartPos;
		xOffset = xOffsetStart + xMouseDiff;
		yOffset = yOffsetStart + yMouseDiff;
	}
}

void render() {
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0, 0, 0));
	// render the map
	map->render(display, xOffset, yOffset);
	// render the tiles
	renderTileLinkedList();
	SDL_UpdateWindowSurface(gWindow);
}

void setTileLinkedList() {
	tileNode * lastNode = nullptr;
	for ( auto const &i : map->getIndexMap() ) {
		int index = i.first;
		Tile * tile = i.second;
		tileNode* temp = new tileNode(tile, lastNode, nullptr, index);
		temp->xPos = index * 100;
		if (lastNode) {
			lastNode->next = temp;
			lastNode = temp;
		}
		else {
			lastNode = temp;
			currentTile = temp;
		}
	}
}

void renderTileLinkedList() {
	currentTile->tile->render(display, currentTile->xPos, 650);
	tileNode *next = currentTile->next;
	while (next != nullptr) {
		next->tile->render(display, next->xPos, 650);
		next = next->next;
	}
	tileNode *prev = currentTile->previous;
	while (prev != nullptr) {
		prev->tile->render(display, prev->xPos, 650);
		prev = prev->previous;
	}
}
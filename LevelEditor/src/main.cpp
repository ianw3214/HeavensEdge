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
Uint32 currentTime, lastTime;
float deltaTime;

Map *map;
int xOffset, yOffset;
int xMouseStartPos, yMouseStartPos;
int xOffsetStart, yOffsetStart;

bool SPACE, LMB;

tileNode * currentTile;

// asset surfaces
SDL_Surface * rectOutline;

// function declarations
bool init();
void cleanUp();

void handleEvents();
void update();
void render();

void setTileLinkedList();
void renderTileLinkedList();
void addTileLinkedListPos(int);

void setMouseOutline();
void renderRectOutline(int, int);

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
		gWindow = SDL_CreateWindow("Heaven's Edge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	// set SDL settings
	SDL_ShowCursor(SDL_DISABLE);
	// initialize variables
	running = true;
	xOffset = 0, yOffset = 0;
	xMouseStartPos = 0, yMouseStartPos = 0;
	xOffsetStart = 0, yOffsetStart = 0;
	currentTime = lastTime = SDL_GetTicks();
	deltaTime = 0.0f;
	// initialize asset surfaces
	rectOutline = IMG_Load(RECT_OUTLINE_FILE_PATH.c_str());
	if (!rectOutline) {
		std::cout << "failed to load: outline1.png; ERROR: " << IMG_GetError() << std::endl;
	}
	return true;
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
			if (e.key.keysym.sym == SDLK_RIGHT) {
				if (currentTile->next) {
					currentTile = currentTile->next;
				}
			}
			if (e.key.keysym.sym == SDLK_LEFT) {
				if (currentTile->previous) {
					currentTile = currentTile->previous;
				}
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
	currentTime = SDL_GetTicks();
	deltaTime = static_cast<float>(currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	map->update();
	if (SPACE && LMB) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		int xMouseDiff = mouseX - xMouseStartPos;
		int yMouseDiff = mouseY - yMouseStartPos;
		xOffset = xOffsetStart + xMouseDiff;
		yOffset = yOffsetStart + yMouseDiff;
	}
	// update the position of tiles if current tile is not centered
	int center = (SCREEN_WIDTH - TILE_WIDTH) / 2;
	if (currentTile->xPos != center) {
		int distance = static_cast<int>(deltaTime * PALETTE_MOVE_SPEED * (currentTile->xPos < center ? 1 : -1));
		int newX = currentTile->xPos + distance;
		// make sure the movement didn't overshoot the center
		if ((newX > center && currentTile->xPos < center) || (newX < center && currentTile->xPos > center)) {
			// otherwise, correct the distance
			distance = center - currentTile->xPos;
		}
		addTileLinkedListPos(distance);
	}
}

void render() {
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0, 0, 0));
	// render the map
	map->render(display, xOffset, yOffset);
	// render the tiles
	renderTileLinkedList();
	// render a rectangle outline where the mouse is
	setMouseOutline();
	SDL_UpdateWindowSurface(gWindow);
}

void setTileLinkedList() {
	int startPos = (SCREEN_WIDTH - TILE_WIDTH) / 2;
	tileNode * lastNode = nullptr;
	for ( auto const &i : map->getIndexMap() ) {
		int index = i.first;
		Tile * tile = i.second;
		tileNode* temp = new tileNode(tile, lastNode, nullptr, index);
		temp->xPos = index * 100 + startPos;
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

void addTileLinkedListPos(int distance) {
	currentTile->xPos += distance;
	tileNode *next = currentTile->next;
	while (next) {
		next->xPos += distance;
		next = next->next;
	}
	tileNode *prev = currentTile->previous;
	while (prev) {
		prev->xPos += distance;
		prev = prev->previous;
	}
}

void setMouseOutline() {
	// get the current position of the mouse
	int x, y;
	SDL_GetMouseState(&x, &y);
	// stop executing the function if the mouse is on the palette
	if (y > 600) return;
	// calulate the offset of the map in relation to the origin
	int xMapOffset = xOffset % 64;
	int yMapOffset = yOffset % 64;
	// if the offset is negative, inverse it (don't think inverse is the right word but whatever)
	if (xMapOffset < 0) xMapOffset = 64 + xMapOffset;
	if (yMapOffset < 0) yMapOffset = 64 + yMapOffset;
	// figure out the position of the rectangle the mouse is hovering over (in relation to origin)
	int xOutline = x / 64;
	int yOutline = y / 64;
	// expand the position back to pixel coordinates and apply the offset
	int xFinalPos = xOutline * 64 + xMapOffset;
	int yFinalPos = yOutline * 64 + yMapOffset;
	// if the offset brings the rectangle out of position, bring it back by a tile
	xFinalPos -= xFinalPos > x ? 64 : 0;
	yFinalPos -= yFinalPos > y ? 64 : 0;
	// finally, render the outline
	renderRectOutline(xFinalPos, yFinalPos);
}

void renderRectOutline(int x, int y) {
	SDL_Rect targetRect = { x - RECT_OUTLINE_MARGIN, y - RECT_OUTLINE_MARGIN, 0, 0};
	if (SDL_BlitSurface(rectOutline, nullptr, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
	}
}
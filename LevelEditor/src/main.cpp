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

enum mode {
	mode_normal,
	mode_collision,
	mode_player
};

// global variables
SDL_Window * gWindow;
SDL_Surface * display;
bool running;
int xCursor, yCursor;
int cursorState;
Uint32 currentTime, lastTime;
float deltaTime;
bool collisionAdd;
mode editorMode;

Map *map;
int xOffset, yOffset;
int xMouseStartPos, yMouseStartPos;
int xOffsetStart, yOffsetStart;

int player_x, player_y;

bool SPACE, LMB;

tileNode * currentTile;

// asset surfaces
SDL_Surface * rectOutline;
SDL_Surface * cursor;
SDL_Surface * cursorPress;
SDL_Surface * overlay;
SDL_Surface * player;
SDL_Surface * tileOverlay;
SDL_Surface * reference;

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

void renderPlayerStart();
void renderRectOutline(int, int);
void renderCursorSymbol();

int main(int argc, char* argv[]) {

	init();

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
	// initialize objects
	map = new Map();
	// initialize variables
	running = true;
	cursorState = 0;
	SDL_GetMouseState(&xCursor, &yCursor);
	xOffset = 0, yOffset = 0;
	xMouseStartPos = 0, yMouseStartPos = 0;
	xOffsetStart = 0, yOffsetStart = 0;
	currentTime = lastTime = SDL_GetTicks();
	deltaTime = 0.0f;
	collisionAdd = true;
	editorMode = mode_normal;
	player_x = 0, player_y = 0;
	// initialize editor setting variables
	if (LOAD_FILE_PATH.size() > 0) {
		map->loadFromFile(LOAD_FILE_PATH);
		player_x = map->getPlayerX();
		player_y = map->getPlayerY();
	}
	else {
		map->setSettings(TILE_WIDTH, TILE_HEIGHT, BASE_MAP_WIDTH, BASE_MAP_HEIGHT, player_x, player_y);
		map->setEmptyMap();
	}
	// initialize asset surfaces
	rectOutline = IMG_Load(RECT_OUTLINE_FILE_PATH.c_str());
	if (!rectOutline) std::cout << "failed to load: outline1.png; ERROR: " << IMG_GetError() << std::endl;
	cursor = IMG_Load(CURSOR_FILE_PATH.c_str());
	if (!cursor) std::cout << "failed to load: cursor.png; ERROR: " << IMG_GetError() << std::endl;
	cursorPress = IMG_Load(CURSOR_PRESS_FILE_PATH.c_str());
	if (!cursorPress) std::cout << "failed to load: cursor_press.png; ERROR: " << IMG_GetError() << std::endl;
	overlay = IMG_Load(OVERLAY_FILE_PATH.c_str());
	if (!overlay) std::cout << "failed to load: overlay.png; ERROR: " << IMG_GetError() << std::endl;
	player = IMG_Load(PLAYER_FILE_PATH.c_str());
	if (!player) std::cout << "failed to load: player.png; ERROR: " << IMG_GetError() << std::endl;
	tileOverlay = IMG_Load(TILE_OVERLAY_FILE_PATH.c_str());
	if (!tileOverlay) std::cout << "failed to load: tile_overlay.png; ERROR: " << IMG_GetError() << std::endl;
	reference = IMG_Load(REFERENCE_FILE_PATH.c_str());
	if (!reference) std::cout << "failed to load: reference.png; ERROR: " << IMG_GetError() << std::endl;
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
			if (e.key.keysym.sym == SDLK_s) {
				map->saveToFile();
			}
			if (e.key.keysym.sym == SDLK_c) {
				if (editorMode != mode_collision) editorMode = mode_collision;
				else editorMode = mode_normal;
			}
			if (e.key.keysym.sym == SDLK_p) {
				if (editorMode != mode_player) editorMode = mode_player;
				else editorMode = mode_normal;
				
			}
			if (e.key.keysym.sym == SDLK_v) {
				collisionAdd = !collisionAdd;
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
				// if space is true, then panning
				if (SPACE) {
					// set the starting mouse position to move map
					SDL_GetMouseState(&xMouseStartPos, &yMouseStartPos);
					xOffsetStart = xOffset, yOffsetStart = yOffset;
				}
				// if the editor is in player editing mode then set the player spawn point
				else if (editorMode == mode_player) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					player_x = static_cast<int>((x - xOffset) / 64);
					player_y = static_cast<int>((y - yOffset) / 64);
					map->setPlayerCoords(player_x, player_y);
				}
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
	// if the left mouse button is clicked and panning is not on
	if (LMB && !SPACE) {
		// change the mouse tile
		int x, y;
		SDL_GetMouseState(&x, &y);
		int target_x = x - xOffset;
		int target_y = y - yOffset;
		if (editorMode == mode_collision) map->editCollision(target_x, target_y, collisionAdd);
		else if (editorMode == mode_normal) map->editTileAt(target_x, target_y, currentTile->index);
	}
	// update the cursor position
	SDL_GetMouseState(&xCursor, &yCursor);
	// update whether the cursor symbol should be shown
	if (LMB) cursorState = 1;
	else cursorState = 0;
}

void render() {
	SDL_FillRect(display, nullptr, SDL_MapRGB(display->format, 0, 0, 0));
	// render the map
	map->render(display, xOffset, yOffset);
	if (editorMode == mode_collision) {
		// render an overlay of white to distinguish between collision and tile mode
		if (SDL_BlitSurface(overlay, nullptr, display, nullptr) < 0) {
			std::cout << "COULDN'T RENDER OVERLAY; ERROR: " << SDL_GetError() << std::endl;
		}
		// render the collision tiles of the map
		map->renderCollisionTiles(display, xOffset, yOffset);
	}
	// render the tiles if normal mode is on
	if (editorMode == mode_normal) renderTileLinkedList();
	// render the player start
	renderPlayerStart();
	// render the reference
	if (SDL_BlitSurface(reference, nullptr, display, nullptr) < 0) {
		std::cout << "COULDN'T RENDER REFERENCE; ERROR: " << SDL_GetError() << std::endl;
	}
	// render a rectangle outline where the mouse is
	setMouseOutline();
	// render the cursor symbol where the cursor is
	renderCursorSymbol();
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
	// render the tile overlay first
	SDL_Rect targetRect = { 0, 620, 0, 0 };
	if (SDL_BlitSurface(tileOverlay, nullptr, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
	}
	// then render all the other tiles
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

void renderPlayerStart() {
	SDL_Rect targetRect = { player_x * 64 + xOffset, player_y * 64 + yOffset, 0, 0 };
	if (SDL_BlitSurface(player, nullptr, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
	}
}

void renderRectOutline(int x, int y) {
	SDL_Rect targetRect = { x - RECT_OUTLINE_MARGIN, y - RECT_OUTLINE_MARGIN, 0, 0};
	if (SDL_BlitSurface(rectOutline, nullptr, display, &targetRect) < 0) {
		std::cout << "Image unable to blit, error: " << SDL_GetError() << std::endl;
	}
}

void renderCursorSymbol() {
	SDL_Rect targetRect = { xCursor - 5, yCursor - 5, 0, 0 };
	SDL_Surface * cursorImage;
	switch (cursorState){
	case 0: {
		cursorImage = cursor;
	} break;
	case 1: {
		cursorImage = cursorPress;
	} break;
	default: {
		cursorImage = cursor;
	}
	}
	if (SDL_BlitSurface(cursorImage, nullptr, display, &targetRect) < 0) {
		std::cout << "COULDN'T RENDER CURSOR" << SDL_GetError() << std::endl;
	}
}
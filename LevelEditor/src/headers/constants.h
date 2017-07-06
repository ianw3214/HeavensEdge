#pragma once

#include <string>

std::string const OUTPUT_FILE_PATH = "levels/test.txt";

std::string const TILE_SHEET_FILE_PATH = "assets/tiles.png";
std::string const RECT_OUTLINE_FILE_PATH = "assets/outline1.png";
std::string const CURSOR_FILE_PATH = "assets/cursor.png";
std::string const CURSOR_PRESS_FILE_PATH = "assets/cursor_press.png";
std::string const COLLISION_TILE_FILE_PATH = "assets/collision.png";
std::string const OVERLAY_FILE_PATH = "assets/overlay.png";

int const TILE_WIDTH = 64;
int const TILE_HEIGHT = 64;

int const BASE_MAP_WIDTH = 20;
int const BASE_MAP_HEIGHT = 20;

// change these to be customizable in the editor
int const PLAYER_START_X = 1;
int const PLAYER_START_Y = 1;

int const SCREEN_WIDTH = 1280;
int const SCREEN_HEIGHT = 720;

int const PALETTE_MOVE_SPEED = 500;

int const RECT_OUTLINE_MARGIN = 2;
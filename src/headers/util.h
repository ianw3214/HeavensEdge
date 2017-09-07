#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "collision.h"
#include "constants.h"

struct menuItem {
	menuItem * previous;
	menuItem * next;
	int ID;
	menuItem(menuItem* a, menuItem* b, int c) : previous(a), next(b), ID(c) {};
};

struct Text {
	SDL_Texture * texture;
	std::string text;
	int w, h;
	// constructors
	Text() : texture(nullptr), text(nullptr), w(0), h(0) {}
	Text(SDL_Texture* _t, std::string _s, int _w, int _h)
		: texture(_t), text(_s), w(_w), h(_h) {}
};

class UTIL {
public:
	// initialization functions to be called in the engine
	static void loadTextures(SDL_Renderer*);
	static SDL_Texture * loadTexture(std::string, SDL_Renderer*);

	static SDL_Texture * getTextureFromId(std::string);

	static void setWindow(SDL_Window*);
	static SDL_Window* getWindow();

	static void setWindowSize(int, int);
	static int getWindowWidth();
	static int getWindowHeight();

	// font related methods
	static void setFont(TTF_Font*);
	static SDL_Texture * getText(const std::string&, SDL_Renderer*);
	static void closeFont();

	// text related methods
	static Text* loadText(SDL_Renderer*, std::string, bool);
	static void loadText(SDL_Renderer*, std::vector<std::string>);
	static Text * getTextTexture(std::string);

	// sound related methods
	static void playTrack(std::string, int, bool);
	static void playTrack(std::string, int, bool, int);
private:
	static std::map<std::string, SDL_Texture*> textureMap;
	static SDL_Window* gameWindow;
	static int screenWidth, screenHeight;

	static TTF_Font * gFont;
	static std::vector<Text*> text;
};
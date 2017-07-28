#include "util.h"

// define static variables
std::map<std::string, SDL_Texture*> UTIL::textureMap;
SDL_Window* UTIL::gameWindow;
int UTIL::screenWidth, UTIL::screenHeight;

// initialization function to be called in engine
void UTIL::loadTextures(SDL_Renderer* renderer) {
	std::ifstream fileStream;
	fileStream.open(TEXTURE_ID_PATH);
	std::string line;
	while (getline(fileStream, line)) {
		std::string token = "";
		int counter = 0;
		std::string ID, path;
		for (char const & c : line) {
			if (c == '#') {
				ID = token;
				token = "";
			}
			else {
				token += c;
			}
		}
		path = token;
		// load the image from the path to a texture
		textureMap[ID] = loadTexture(path, renderer);
	}
	return;
}

SDL_Texture * UTIL::getTextureFromId(std::string ID) {
	return textureMap[ID];
}

SDL_Texture* UTIL::loadTexture(std::string path, SDL_Renderer * renderer) {
	// the final texture to return
	SDL_Texture * texture = NULL;

	// load the image onto a surface first
	SDL_Surface * loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) std::cout << "Unable to load image: " << path << ", ERROR: " << IMG_GetError() << std::endl;
	else {
		// create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL) std::cout << "Unable to create texture: " << path << ", ERROR: " << SDL_GetError() << std::endl;
		// get rid of the loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return texture;
}

void UTIL::setWindow(SDL_Window* inpWindow) {
	gameWindow = inpWindow;
}
SDL_Window* UTIL::getWindow() {
	return gameWindow;
}

void UTIL::setWindowSize(int w, int h) {
	screenWidth = w;
	screenHeight = h;
}
int UTIL::getWindowWidth() { return screenWidth; }
int UTIL::getWindowHeight() { return screenHeight; }
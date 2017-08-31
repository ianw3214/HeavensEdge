#include "util.h"

// define static variables
std::map<std::string, SDL_Texture*> UTIL::textureMap;
SDL_Window* UTIL::gameWindow;
int UTIL::screenWidth, UTIL::screenHeight;

TTF_Font * UTIL::gFont;
std::vector<Text*> UTIL::text;

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

void UTIL::setFont(TTF_Font* font) { gFont = font; }

SDL_Texture * UTIL::getText(const std::string& input, SDL_Renderer* renderer) {
	SDL_Color colour = { 255, 255, 255 };
	SDL_Texture * returnTexture = nullptr;
	SDL_Surface * textSurface = TTF_RenderText_Solid(gFont, input.c_str(), colour);
	if (textSurface == NULL)
		std::cout << "Unable to render text: " << input << ", ERROR: " << TTF_GetError() << std::endl;
	else {
		// create the texture
		returnTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (returnTexture == NULL)
			std::cout << "Unable to create texture from rendered text, ERROR: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(textSurface);
	}
	return returnTexture;
}

void UTIL::closeFont() {
	TTF_CloseFont(gFont);
	gFont = NULL;
}

Text* UTIL::loadText(SDL_Renderer* renderer, const std::string inputText, bool cache) {
	SDL_Texture * temp = getText(inputText, renderer);
	if (temp == NULL) {
		std::cout << "Unable to load text: " << inputText << std::endl;
		return nullptr;
	}
	int width, height;
	SDL_QueryTexture(temp, NULL, NULL, &width, &height);
	Text * tempText = new Text(temp, inputText, width, height);
	if (cache)
		text.push_back(tempText);
	return tempText;
}

void UTIL::loadText(SDL_Renderer* renderer, std::vector<std::string> inputText) {
	for (std::string const & str : inputText) {
		loadText(renderer, str, true);
	}
}

Text * UTIL::getTextTexture(std::string str) {
	for (Text* const e : text) {
		if (e->text == str) {
			return e;
		}
	}
	// return a nullptr if the desired string was not found
	return nullptr;
}
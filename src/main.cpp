#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "engine.h"
#include "menu.h"
#include "level.h"

#include "constants.h"

int main(int argc, char* argv[]){

	// create a game engine and initialize it, quit if an error occured
    Engine game(WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game.init()) { return 1; }
	// Menu* test = new Menu();
	Level* test = new Level("levels/test.txt");
	game.setState(test);
    while(game.isRunning()){
		game.update();
    }
    game.cleanUp();

    return 0;

}

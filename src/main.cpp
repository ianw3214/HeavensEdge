#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "engine.h"
#include "menu.h"
#include "level.h"

int main(int argc, char* argv[]){

    Engine game(1280, 720);
	Menu* test = new Menu();
	// Level* test = new Level("levels/test.txt");
	// return an error if the engine can't initialize with the starting level
    if(!game.init(test)){ return 1; }
    while(game.isRunning()){
        game.handleEvents();
        game.render();
		game.update();
    }

    game.cleanUp();

    return 0;

}

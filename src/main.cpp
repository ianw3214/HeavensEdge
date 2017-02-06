#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "engine.h"

int main(int argc, char* argv[]){

    Engine game;
    State* test = new State();
    if(!game.init(test)){
        return 1;
    }
    while(game.isRunning()){
        game.handleEvents();
        game.update();
        game.render();
    }

    game.cleanUp();

    return 0;

}

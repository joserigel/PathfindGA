#include <SDL3/SDL_init.h>
#include <iostream>

#include "display.hpp"
#include "neuralnet.hpp"
#include "board.hpp"

using namespace std;

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        return -1;
    }
    
    Display display;
    Board board(display.width, display.height);
    board.generate(0.20);
    display.update(board);
    display.start();

    SDL_Quit();

    return 0;
}

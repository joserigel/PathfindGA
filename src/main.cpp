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
    size_t width = 15;
    size_t height = 7;
    size_t circles = 10;
    Display display(width, height, circles);
    Board board(width, height, circles);
    board.generate(0.30);
    display.update(board);
    display.start();

    SDL_Quit();

    return 0;
}

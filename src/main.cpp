#include <SDL3/SDL_init.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "display.hpp"
#include "training.hpp"
#include "board.hpp"

using namespace std;

void trainingThread(Training& training, Board& board, Display& display) {
    for (int iter = 0; !display.done() && iter < 30; iter++) {
        cout << "iter: " << iter << endl;
        training.clear();
        board.reset();
        for (int i = 0; i < board.width() - 1; i++) {
            training.tick(board);
            display.update(board);
        }
        training.pickAndMutate(max(0.05 - 0.003 * iter, 0.01));
    }
}

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        return -1;
    }
    size_t width = 15;
    size_t height = 7;
    size_t instances = 100;
    Display display(width, height, instances);
    Board board(width, height, instances);
    Training training(width, height, instances);
    board.generate(0.30);
    std::thread t(&trainingThread, std::ref(training), std::ref(board), std::ref(display));
    display.start(board);
    t.join();
    SDL_Quit();

    return 0;
}

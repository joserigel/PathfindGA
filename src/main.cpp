#include <SDL3/SDL_init.h>
#include <iostream>

#include "display.hpp"
#include "neuralnet.hpp"

using namespace std;

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        return -1;
    }
    
    Display display;
    NeuralNet neuralNet(display.width, display.height);
    Eigen::VectorXd input(display.width * display.height);
    Eigen::VectorXd output = neuralNet.feed(input);

    cout << output << endl;

    display.start();
    SDL_Quit();

    return 0;
}

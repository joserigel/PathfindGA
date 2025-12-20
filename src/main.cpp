#include "display.hpp"
#include <SDL3/SDL_init.h>
using namespace std;

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        return -1;
    }

    Display display;
    display.start();
    SDL_Quit();
    return 0;
}

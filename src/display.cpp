#include "display.hpp"
#include <cstdint>

Display::~Display() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    if (displayThread) {
        delete displayThread;
    }
}

Display::Display() {
    srand(time(NULL));

    window = SDL_CreateWindow(
            title, width, height,
            0
        );
    renderer = SDL_CreateRenderer(
            window, NULL
        );
    texture = SDL_CreateTexture(
            renderer, 
            SDL_PixelFormat::SDL_PIXELFORMAT_ABGR8888, 
            SDL_TextureAccess::SDL_TEXTUREACCESS_STREAMING,
            width, height
        );
    
    done = false;

    frameBuffer = new uint8_t[width * height * 4];
    if (!window || !renderer || !texture) {
        throw std::runtime_error("Cannot initialize SDL graphics");
    }
}

void Display::loop() {
    while (!done) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                size_t coords = (i * width * 4) + j * 4;
                frameBuffer[coords + 0] = rand() % 256;
                frameBuffer[coords + 1] = rand() % 256;
                frameBuffer[coords + 2] = rand() % 256;
                frameBuffer[coords + 3] = 255;
            }
        }
    }
}

void Display::start() {
    displayThread = new std::thread(&Display::loop, this); 
    while(!done) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_EventType::SDL_EVENT_QUIT) {
                done = true; 
            }
        }
        Uint64 aTicks = SDL_GetTicks();
        
        unsigned char* pixels;
        int pitch;
         
        SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch);
        std::copy(
                frameBuffer, 
                frameBuffer + (width * height * 4), 
                pixels
            ); 
        SDL_UnlockTexture(texture);  
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }
    displayThread->join();
}

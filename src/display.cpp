#include "display.hpp"

#include <SDL3/SDL_render.h>
#include <ctime>
#include <stdexcept>

#include <SDL3/SDL_timer.h>

Display::~Display() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(circleTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    if (displayThread) {
        delete displayThread;
    }
}

Display::Display() {
    srand(time(NULL));

    window = SDL_CreateWindow(
            title, 
            width * windowScale, height * windowScale,
            0
        );
    renderer = SDL_CreateRenderer(
            window, NULL
        );
    backgroundTexture = SDL_CreateTexture(
            renderer, 
            SDL_PixelFormat::SDL_PIXELFORMAT_ABGR8888, 
            SDL_TextureAccess::SDL_TEXTUREACCESS_STATIC,
            width, height
        );
    backgroundRect.h = height * windowScale;
    backgroundRect.w = width * windowScale;
    backgroundRect.x = 0;
    backgroundRect.y = 0;

    uint8_t* backgroundBMP = new uint8_t[width * height * 4];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            size_t coords = (i * width * 4) + j * 4;
            uint8_t color = (i + j) % 2 == 0 ? 255 : 0;
            backgroundBMP[coords + 0] = color; 
            backgroundBMP[coords + 1] = color;
            backgroundBMP[coords + 2] = color;
            backgroundBMP[coords + 3] = 255;
        }
    }
    SDL_UpdateTexture(backgroundTexture, 
            NULL, backgroundBMP, width * 4);
    delete[] backgroundBMP;
            
    // Circle Texture
    circleTexture = SDL_CreateTexture(
            renderer,
            SDL_PixelFormat::SDL_PIXELFORMAT_ABGR8888,
            SDL_TextureAccess::SDL_TEXTUREACCESS_STATIC,
            windowScale, windowScale
        );
    SDL_SetTextureScaleMode(backgroundTexture,
            SDL_ScaleMode::SDL_SCALEMODE_NEAREST);
    
    uint8_t* circleBMP = new uint8_t[windowScale * windowScale * 4];
    for (int i = 0; i < windowScale; i++) {
        for (int j = 0; j < windowScale; j++) {
            int coords = (i * windowScale * 4) + j * 4;
            int r = windowScale / 2;
            int x = j - r;
            int y = i - r;
            if (x * x + y * y < r * r) {
                circleBMP[coords + 0] = 255;
                circleBMP[coords + 1] = 0;
                circleBMP[coords + 2] = 0;
                circleBMP[coords + 3] = 255;
            } else {
                circleBMP[coords + 3] = 0;
            }
        }
    }

    circleRect.h = windowScale;
    circleRect.w = windowScale;
    circleRect.x = 0;
    circleRect.y = 0;

    SDL_UpdateTexture(circleTexture, NULL, circleBMP, windowScale * 4);

    delete[] circleBMP;
    
    done = false;

    if (!window || !renderer || !backgroundTexture || !circleTexture) {
        throw std::runtime_error("Cannot initialize SDL graphics");
    }

}

void Display::loop() {
    
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
        
        SDL_RenderTexture(renderer, 
                backgroundTexture, NULL, &backgroundRect);
        SDL_RenderTexture(renderer, 
                circleTexture, NULL, &circleRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }
    displayThread->join();
}

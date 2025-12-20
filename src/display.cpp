#include "display.hpp"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_keycode.h>

#include <stdexcept>
#include <ctime>


Display::~Display() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(circleTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

Display::Display(size_t width, size_t height, size_t circles)
    : width(width), height(height), circles(circles) {

    window = SDL_CreateWindow(
            title, 
            width * windowScale, height * windowScale,
            0
        );
    renderer = SDL_CreateRenderer(
            window, NULL
        );

    // Background Texture
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
                circleBMP[coords + 1] = 255;
                circleBMP[coords + 2] = 255;
                circleBMP[coords + 3] = 255;
            } else {
                circleBMP[coords + 3] = 0;
            }
        }
    }

    for (auto& circle : this->circles) {
        circle.h = windowScale;
        circle.w = windowScale;
        circle.x = 0;
        circle.y = (int)(height / 2) * windowScale;
    }

    SDL_UpdateTexture(circleTexture, NULL, circleBMP, windowScale * 4);

    delete[] circleBMP;
    
    done = false;

    if (!window || !renderer || !backgroundTexture || !circleTexture) {
        throw std::runtime_error("Cannot initialize SDL graphics");
    }

}

void Display::update(Board board) {
    vector<vector<bool>> boardVector = board.obstacles();
    uint8_t* backgroundBMP = new uint8_t[width * height * 4];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            uint8_t color = boardVector[j][i] ? 255 : 0;
            size_t coords = (i * width * 4) + j * 4;
            backgroundBMP[coords + 0] = color;
            backgroundBMP[coords + 1] = color;
            backgroundBMP[coords + 2] = color;
            backgroundBMP[coords + 3] = 255;
        }
    }
    SDL_UpdateTexture(backgroundTexture,
            NULL, backgroundBMP, width * 4);
    delete[] backgroundBMP;
}

void Display::start() {

    while(!done) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_EventType::SDL_EVENT_QUIT) {
                done = true; 
            }

            if (e.type == SDL_EventType::SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE) {
                done = true;
            }
        }
        
        SDL_RenderTexture(renderer, 
                backgroundTexture, NULL, &backgroundRect);
        srand(0);
        for (auto& circle : circles) {
            SDL_SetTextureColorMod(circleTexture,
                    rand() % 256, rand() % 256, rand() % 256);
            SDL_RenderTexture(renderer,
                circleTexture, NULL, &circle);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }
}

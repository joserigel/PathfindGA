#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include "board.hpp"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <vector>

class Display {
    private:
        static constexpr size_t windowScale = 32;

        size_t width;
        size_t height;

        const char* title = "PathfindRL";
        SDL_Window* window;
        SDL_Renderer* renderer;

        SDL_Texture* backgroundTexture;
        SDL_FRect backgroundRect;

        SDL_Texture* circleTexture;
        std::vector<SDL_FRect> circles;

        bool done;
    public:
        Display(size_t width, size_t height, size_t circles);
        ~Display();

        void start();
        void update(Board board);
};

#endif /* __DRAW_HPP__ */

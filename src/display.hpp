#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include "board.hpp"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class Display {
  private:
   const char* title = "PathfindRL";
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* backgroundTexture;
    SDL_FRect backgroundRect;

    SDL_Texture* circleTexture;
    SDL_FRect circleRect;

    bool done; 
  public:
    static constexpr size_t  width = 15;
    static constexpr size_t height = 7;
    static constexpr size_t windowScale = 32;
 
    Display();
    ~Display();

    void start();
    void update(Board board);
};

#endif /* __DRAW_HPP__ */

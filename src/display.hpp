#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <cstdint>
#include <thread>


#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class Display {
  private:
    static constexpr int width = 30;
    static constexpr int height = 15;
    static constexpr int windowScale = 32;
    const char* title = "PathfindRL";
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* backgroundTexture;
    SDL_FRect backgroundRect;

    SDL_Texture* circleTexture;
    SDL_FRect circleRect;

    std::thread* displayThread;    
    bool done; 
    void loop();
  public:
    Display();
    ~Display();

    void start();
};

#endif /* __DRAW_HPP__ */

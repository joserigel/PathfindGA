#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <thread>


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

    std::thread* displayThread;    
    bool done; 
    void loop();
  public:
    static constexpr size_t width = 15;
    static constexpr size_t height = 8;
    static constexpr size_t windowScale = 32;
 
    Display();
    ~Display();

    void start();
};

#endif /* __DRAW_HPP__ */

#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <thread>
#include <time.h>
#include <stdexcept>

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>

class Display {
  private:
    static constexpr int width = 800;
    static constexpr int height = 600;
    const char* title = "PathfindRL";
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    uint8_t* frameBuffer;
    std::thread* displayThread;    
    bool done; 
    void loop();
  public:
    Display();
    ~Display();

    void start();
};

#endif /* __DRAW_HPP__ */

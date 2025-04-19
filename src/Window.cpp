#include "Window.h"

using namespace ShooterTrainer;

RangeSession::RangeSession() {

}
RangeSession::~RangeSession() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;
}
bool RangeSession::init(SDL_Window* setWindow, SDL_Renderer* setRenderer) {
    window      = setWindow;
    renderer    = setRenderer; 

    if(window){
        if(!renderer)
            renderer = SDL_CreateRenderer(window, NULL);
        
        return renderer && window; // Perform check on renderer to see if made properly and return
    }

    return SDL_CreateWindowAndRenderer(TITLE, WIDTH, HEIGHT, 0, &window, &renderer);
}

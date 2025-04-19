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

    return SDL_CreateWindowAndRenderer(TITLE, WIDTH, HEIGHT, FLAGS, &window, &renderer);
}
void RangeSession::run(){
    if(!window || !renderer)
        throw std::runtime_error("Must initialize before running");

    bool quit { false };

    SDL_Event e;
    SDL_zero(e);

    while(!quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_EVENT_QUIT)
                quit = true;
        }
                
        //Fill the background 
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        // Update renderer
        SDL_RenderPresent(renderer);
    }
}



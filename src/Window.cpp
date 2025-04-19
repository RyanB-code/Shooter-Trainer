#include "Window.h"

using namespace ShooterTrainer;

Window::Window(const char* setTitle, int setWidth, int setHeight){
    window = SDL_CreateWindow(setTitle, setWidth, setHeight, 0);
}
Window::~Window(){
    SDL_DestroyWindow(window);
    window = nullptr;
}
SDL_Window* Window::getWindow() const {
    return window;
}

Renderer::Renderer(SDL_Window* window){
    renderer = SDL_CreateRenderer(window, NULL);
}
Renderer::~Renderer(){
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
}
SDL_Renderer* Renderer::getRenderer() const {
    return renderer;
}

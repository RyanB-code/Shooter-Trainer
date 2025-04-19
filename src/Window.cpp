#include "Window.h"

using namespace ShooterTrainer;

Window::Window(){

}
Window::~Window(){

}
bool Window::init(){
    if(!SDL_CreateWindowAndRenderer(TITLE, HEIGHT, WIDTH, 0, &window, &renderer))
		return false;
	
    return true;
}
void Window::destroy(){
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

    return
}



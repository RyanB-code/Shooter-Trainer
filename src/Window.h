#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>

namespace ShooterTrainer{

    class Window {
    public:
        Window(const char* setTitle, int setWidth, int setHeight);
        ~Window();

        SDL_Window* getWindow () const;
    private:
        SDL_Window* 	window		{ nullptr };
    };

    class Renderer {
    public:
        Renderer(SDL_Window* window);
        ~Renderer();

        SDL_Renderer* getRenderer() const;
    private:
        SDL_Renderer* renderer { nullptr };
    };

}

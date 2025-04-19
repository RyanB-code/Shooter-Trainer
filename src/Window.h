#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>


namespace ShooterTrainer{

    class Window {
    public:
        Window();
        ~Window();

        bool init();
        void destroy();

    private:
        static constexpr char   TITLE[] { "Shooter Trainer" };
        static constexpr int    HEIGHT  { 640 };
        static constexpr int    WIDTH   { 800 };

        SDL_Renderer* 	renderer 	{ nullptr };
        SDL_Window* 	window		{ nullptr };
    };

}

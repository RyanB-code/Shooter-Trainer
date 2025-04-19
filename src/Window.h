#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>

namespace ShooterTrainer{

    class RangeSession {
    public:
        RangeSession();
        ~RangeSession();

        bool init(SDL_Window* window=nullptr, SDL_Renderer* renderer=nullptr);

    private:
        static constexpr char   TITLE[] { "Shooter Trainer" };
        static constexpr int    WIDTH   { 640 };
        static constexpr int    HEIGHT  { 800 };

        SDL_Window*     window      { nullptr };
        SDL_Renderer*   renderer    { nullptr };
    };

}

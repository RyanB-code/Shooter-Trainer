#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>



namespace ShooterTrainer{

    namespace Framework{
        
        class Framework final {
        public:
            Framework();
            ~Framework();

            bool setup();
            void run();
        private:
            LoggerPtr logger;

    }
}

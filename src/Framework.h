#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Logger.h"

using namespace ShooterTrainer::Logging;

namespace ShooterTrainer::Framework{
    class Framework final {
    public:
        Framework(LoggerPtr setLogger=nullptr);
        ~Framework();

        bool setup();
        void run();
    private:
        LoggerPtr logger;

        bool setupLogger();
    };
}

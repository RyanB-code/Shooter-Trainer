#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Logger.h"
#include "Window.h"
#include "AssetManager.h"

using namespace ShooterTrainer::Logging;

namespace ShooterTrainer::Framework{
    class Framework final {
    public:
        Framework();
        ~Framework();

        bool setup();
        void run();
    private:
        AssetManager assetManager;

        bool setupLogger();
        bool setupAssetManager();
    };
}

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include <filesystem>
#include <fstream>
#include <iostream>

namespace ShooterTrainer {

    struct Directories{
        std::string parent;
        
        std::string assets;
    };

    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        bool setupFilesystem(const std::string& setParentDirectory);
    private:
        Directories directories;
    };

    bool ensureDirectory (const std::string& path);
    bool ensureFile     (const std::string& path);
}


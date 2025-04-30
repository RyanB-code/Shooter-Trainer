#include "Framework.h"

namespace ShooterTrainer::Framework{

Framework::Framework(LoggerPtr setLogger) : logger {setLogger}{

}
Framework::~Framework(){

}
bool Framework::setup() {
    if(!logger){
        if(!setupLogger()){
            std::puts("Failed to start logging system.\nApplication aborted.");
            return false;
        }
    }

    logger->log_info("Setup Logger");

    if(!setupAssetManager()){
        logger->log_critical("Cannot setup Asset Manager. Application aborted");
        return false;
    }
    
    logger->log_info("Setup Asset Manager");

    return true;
}
void Framework::run(){
    if(!SDL_Init(SDL_INIT_VIDEO)){
		logger->log_critical("SDL could not initialize");
        logger->log_SDL();
		return;
	}


    // Window
    Window window;

    if(!window.init()){
        logger->log_info("Could not make window");
        logger->log_SDL();
    }
    

    SDL_Quit();
}


bool Framework::setupLogger() {
    using namespace ShooterTrainer::Logging;
    
    LogSettings settings;
    settings.textWidth_tag  = 10;
    settings.textWidth_msg  = 100;
    settings.showLocation   = false;

    logger = std::make_shared<Logger>(Logger{settings});
    if(!logger->addOutput(std::make_shared<LogToConsole>(LogToConsole{ }))){
        std::puts("Could not add Console Logging as a Logger Output");
        return false;
    }

    logger->setAllSettings(settings);

    return true;
}
bool Framework::setupAssetManager(){
    // Carried over from LAS
    #ifdef __linux__
        std::string exePath {std::filesystem::canonical(std::filesystem::path{"/proc/self/exe"})};
        std::string parentDir;

        // Iterates backwards over the EXE path and just goes until it finds the first slash and then returns that string
        for(int i{static_cast<int>(exePath.length())-1}; i >= 0; --i){
            char c {exePath.at(i)};
            if(c == '/' || c == '\\'){
                parentDir = exePath.substr(0, ++i);
                break;
            }
        }
    #else
        std::cerr << "Only Linux is currently supported.\n";
        return false;
    #endif

    parentDir += "Testing/";

    return assetManager.setupFilesystem(parentDir);
}

}

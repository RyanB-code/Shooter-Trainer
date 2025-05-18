#include "Framework.h"

namespace ShooterTrainer::Framework{

Framework::Framework() {

}
Framework::~Framework(){

}
bool Framework::setup() {
    if(!setupLogger()){
        std::puts("Failed to start logging system.\nApplication aborted.");
        return false;
    }

    log_info("Setup Logger");

    if(!setupAssetManager()){
        log_critical("Cannot setup Asset Manager. Application aborted");
        return false;
    }
    
    log_info("Setup Asset Manager");

    return true;
}
void Framework::run(){
    if(!SDL_Init(SDL_INIT_VIDEO)){
		log_critical("SDL could not initialize");
        log_SDL();
		return;
	}

    RangeSession session;

    if(!session.init()){
        log_info("Failed to init range session");
        SDL_Quit();
        return;
    }

    try{
        session.run();
    }
    catch(std::exception& e){
        std::puts(e.what());
    }

    SDL_Quit();

}


bool Framework::setupLogger() {
    using namespace ShooterTrainer::Logging;
    
    LogSettings settings;
    settings.textWidth_tag  = 10;
    settings.textWidth_msg  = 100;
    settings.showLocation   = false;

    if(!addOutput(std::make_shared<LogToConsole>(LogToConsole{ }))){
        std::puts("Could not add Console Logging as a Logger Output");
        return false;
    }

    setAllSettings(settings);

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

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

    return true;
}
void Framework::run(){
    logger->log_info("Test Log");
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


}

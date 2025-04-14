#include <iostream>

#include "Logger.h"

using namespace ShooterTrainer::Logging;

class LogToConsole final : public LogOutput {
public:
    LogToConsole(){ }
    ~LogToConsole(){ }

    void log(const Log& log) const override{
        std::ostringstream os;

        if(settings.showTime)
            os << '[' << printTime(log.timestamp) << "] ";

        if(settings.showTags)
            os << std::format("[{:^{}}] ", log.tag, settings.textWidth_tag);  // Centers the tag

        if(settings.showMsg)
            os << std::format("{:<{}} ", log.msg, settings.textWidth_msg);  // Left-align the msg

        if(settings.showLocation)
            os << printLocation(log.location);

        std::cout << os.str() << '\n';
    }
};


int main() {
    LogToConsole consoleLog { };

    LogSettings settings;
    settings.textWidth_tag = 10;
    settings.textWidth_msg = 50;

    Logger logger { settings };

    logger.addOutput(std::make_shared<LogToConsole>(consoleLog));

    logger.setAllSettings(settings);

    logger.log("Normal tag", "TAG");

    settings.textWidth_tag = 20;

    logger.setSettings(1, settings);

    logger.log("Test Log", "TAG");

    return 0;
}

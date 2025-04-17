#include <iostream>

#include "Framework.h"


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

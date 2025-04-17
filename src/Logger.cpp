#include "Logger.h"

namespace ShooterTrainer::Logging {

    LogOutput::LogOutput(const LogSettings& setSettings) : settings { setSettings } {
        static int givenIDs { 0 };

        if(givenIDs < 0 || givenIDs > 50) 
            throw::std::out_of_range("Max LogOutputs reached: 50");

        ID = ++givenIDs;
    }
    LogOutput::~LogOutput(){

    }

    void LogOutput::setSettings(const LogSettings& setSettings){
        settings = setSettings;
    }
    LogSettings LogOutput::getSettings() const {
        return settings;
    }
    int LogOutput::getID() const {
        return ID;
    }


    Logger::Logger(const LogSettings& setSettings) : settings { setSettings } {

    }
    Logger::~Logger(){

    }
    void Logger::log(const std::string& msg, const std::string& tag, const std::source_location& location) const {
        if(outputs.empty())
            return;

        const std::chrono::zoned_time time { std::chrono::current_zone(), std::chrono::system_clock::now() };

        Log log {msg, tag, location, time};

        for(const auto& [ID, outputPtr] : outputs)
            outputPtr->log(log);

        return;
    }
    void Logger::log_info(const std::string& msg, const std::source_location& location) const {
        log(msg, "INFO", location);
    }
    void Logger::log_warn(const std::string& msg, const std::source_location& location) const {
        log(msg, "WARNING", location);
    }
    void Logger::log_error(const std::string& msg, const std::source_location& location) const {
        log(msg, "ERROR", location);
    }
    void Logger::log_critical(const std::string& msg, const std::source_location& location) const {
        log(msg, "CRITICAL", location);
    }
    bool Logger::addOutput(LogOutputPtr newOutput) {
        if(outputs.contains(newOutput->getID()))
            return false;

        return outputs.try_emplace(newOutput->getID(), newOutput).second;
    }
    bool Logger::removeOutput(int ID) {
        auto iterator { outputs.find(ID) };

        if(iterator != outputs.end()){
            outputs.erase(iterator);
            return true;
        }

        return false;
    }
    void Logger::setAllSettings(const LogSettings& setSettings){
        settings = setSettings;

        for(auto& [ID, outputPtr] : outputs)
            outputPtr->setSettings(settings);
    }
    bool Logger::setSettings(int ID, const LogSettings& setSettings){
        if(!outputs.contains(ID))
            return false;

        outputs.at(ID)->setSettings(setSettings);

        return true;
    }
    LogSettings Logger::getAllSettings() const {
        return settings;
    }
    LogSettings Logger::getSettings(int ID) const{
        if(!outputs.contains(ID))
            throw std::out_of_range("A LogOutput with that ID is not active");

        return outputs.at(ID)->getSettings();
    }

    std::string printTime(const std::chrono::system_clock::time_point& time){
        std::chrono::zoned_time zonedTime { std::chrono::current_zone(), time };

 //       std::string seconds {std::format("{:%S}", zonedTime)};

        return std::format("{:%T}", zonedTime).substr(0, 8);
    }
    std::string printLocation(const std::source_location& location){
        std::ostringstream os;

        os << '[' << location.file_name() << " | " << location.function_name() << " | " << location.line() << ']';

        return os.str();
    }


    // Log To Console
    LogToConsole::LogToConsole(){

    }
    LogToConsole::~LogToConsole(){

    }
    void LogToConsole::log(const Log& log) const {
        std::ostringstream os;

        if(settings.showTime)
            os << '[' << printTime(log.timestamp) << "] ";

        if(settings.showTags)
            os << std::format("[{:^{}}] ", log.tag, settings.textWidth_tag);  // Centers the tag

        if(settings.showMsg)
            os << std::format("{:<{}} ", log.msg, settings.textWidth_msg);  // Left-align the msg

        if(settings.showLocation)
            os << printLocation(log.location);

        std::puts(os.str().c_str());
    }

}

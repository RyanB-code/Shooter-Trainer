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


    Logger::Logger() {

    }
    Logger::~Logger(){

    }
    Logger& Logger::getInstance() {
        static Logger instance;
        return instance;
    }
    void Logger::log(const std::string& msg, const std::string& tag, const std::source_location& location) const {
        if(outputs.empty()){
            std::puts("There are no log outputs.");
            return;
        }

        const std::chrono::zoned_time time { std::chrono::current_zone(), std::chrono::system_clock::now() };

        Log log {msg, tag, location, time};

        for(const auto& [ID, outputPtr] : outputs)
            outputPtr->log(log);

        return;
    }
    bool Logger::addOutput(LogOutputPtr newOutput) {
        if(outputs.contains(newOutput->getID()))
            return false;

        return outputs.try_emplace(newOutput->getID(), newOutput).second;
    }
    bool Logger::contains(int ID) const {
        return outputs.contains(ID);
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

    // Helper Functions
    std::string printTime(const std::chrono::system_clock::time_point& time){
        std::chrono::zoned_time zonedTime { std::chrono::current_zone(), time };

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

namespace ShooterTrainer{
    void log_info(const std::string& msg, const std::source_location& location) {
        Logging::Logger::getInstance().log(msg, "INFO", location);
    }
    void log_warn(const std::string& msg, const std::source_location& location) {
        Logging::Logger::getInstance().log(msg, "WARNING", location);
    }
    void log_error(const std::string& msg, const std::source_location& location) {
        Logging::Logger::getInstance().log(msg, "ERROR", location);
    }
    void log_critical(const std::string& msg, const std::source_location& location) {
        Logging::Logger::getInstance().log(msg, "CRITICAL", location);
    }
    void log_SDL(const std::source_location& location) {
        Logging::Logger::getInstance().log(std::format("SDL Error: {:}", SDL_GetError()), "SDL", location);
    }

    bool Logging::addOutput(LogOutputPtr newOutput) {
        return Logger::getInstance().addOutput(newOutput);
    }
    bool Logging::removeOutput(int ID) {
        return Logger::getInstance().removeOutput(ID);
    }
    void Logging::setAllSettings(const LogSettings& setSettings){
        return Logger::getInstance().setAllSettings(setSettings);
    }
    bool Logging::setSettings(int ID, const LogSettings& setSettings){
        return Logger::getInstance().setSettings(ID, setSettings);
    }
    Logging::LogSettings Logging::getAllSettings() {
        return Logger::getInstance().getAllSettings();
    }
    Logging::LogSettings Logging::getSettings(int ID) {
        return Logger::getInstance().getSettings(ID);
    }
}

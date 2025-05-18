#pragma once

#include <format>
#include <source_location>
#include <string>
#include <memory>
#include <filesystem>
#include <chrono>
#include <map>

#include <SDL3/SDL.h>

namespace ShooterTrainer::Logging{
    
    // Forward Delcarations
    class LogOutput;
    class Logger;

    // Aliases
    using LoggerPtr         = std::shared_ptr<Logger>;
    using ConstLoggerPtr    = std::shared_ptr<const Logger>;

    using LogOutputPtr      = std::shared_ptr<LogOutput>;
    using ConstLogOutputPtr = std::shared_ptr<const LogOutput>;

    struct LogSettings {
        bool showTime       { true };
        bool showTags       { true };
        bool showMsg        { true };
        bool showLocation   { true };

        int textWidth_tag   { 9 };
        int textWidth_msg   { 50 };
    };

    struct Log {
        const std::string           msg;
        const std::string           tag;
        const std::source_location  location;

        const std::chrono::time_point<std::chrono::system_clock> timestamp;
    };

    class LogOutput {
    public:
        LogOutput(const LogSettings& setSettings=LogSettings{ }); // No more than 50 outputs allowed. Throws out of range if exceeded
        virtual ~LogOutput();

        void        setSettings (const LogSettings& setSettings);
        LogSettings getSettings () const;
        int         getID       () const;

        virtual void log(const Log& log) const = 0;

    protected:
        LogSettings settings;
    private:
        int ID;
    };

    class Logger {
    public:
        ~Logger();

        static Logger& getInstance();

        void log            (const std::string& msg, const std::string& tag, const std::source_location& location=std::source_location::current()) const;
        bool addOutput      (LogOutputPtr output);
        bool contains       (int ID) const;
        bool removeOutput   (int outputID);

        void        setAllSettings  (const LogSettings& setSettings);
        bool        setSettings     (int ID, const LogSettings& setSettings);

        LogSettings getAllSettings  () const;
        LogSettings getSettings     (int ID) const; // Throws out_of_range if not there

    private:
        Logger();
        Logger(const Logger& other) = delete;
        Logger& operator=(const Logger& other) = delete;

        LogSettings settings { };
        std::map<int, LogOutputPtr> outputs { };
    };

    // Helper Functions
    std::string printTime       (const std::chrono::system_clock::time_point& time);
    std::string printLocation   (const std::source_location& location);

    // Log To Console
    class LogToConsole final : public LogOutput {
    public:
        LogToConsole();
        ~LogToConsole();

        void log(const Log& log) const;
    };

}

namespace ShooterTrainer {
    void log            (const std::string& msg, const std::string& tag, const std::source_location& location=std::source_location::current());
    void log_info       (const std::string& msg, const std::source_location& location=std::source_location::current());
    void log_warn       (const std::string& msg, const std::source_location& location=std::source_location::current());
    void log_error      (const std::string& msg, const std::source_location& location=std::source_location::current());
    void log_critical   (const std::string& msg, const std::source_location& location=std::source_location::current());
    void log_SDL        (const std::source_location& location=std::source_location::current());

    namespace Logging {
        bool addOutput      (LogOutputPtr output);
        bool removeOutput   (int outputID);

        void        setAllSettings  (const LogSettings& setSettings);
        bool        setSettings     (int ID, const LogSettings& setSettings);

        LogSettings getAllSettings  ();
        LogSettings getSettings     (int ID); // Throws out_of_range if not there
    }
}

#include <format>
#include <source_location>
#include <string>
#include <memory>
#include <filesystem>


namespace ShooterTrainer::Logging{

    struct LogSettings {
        bool showTime       { true };
        bool showTags       { true };
        bool showMsg        { true };
        bool showLocation   { true };

        int textWidth_tag   { 5 };
        int textWidth_msg   { 50 };
    };

    class LogOutput {
    public:
        LogOutput(const LogSettings& setSettings);
        virtual ~LogOutput();

        bool        setSettings (const LogSettings& setSettings);
        LogSettings getSettungs () const;
        int         getID       () const;

        virtual bool log(const Log& log) const = 0;

    protected:
        LogSettings settings;
        const int ID;
    };

    class Logger {
    public:
        Logger(const LogSettings& setLogSettings);
        virtual ~Logger();

        void log(const std::string& msg, const std::string& tag, const std::source_location& setLocation= std::source_location::current()) const;

        bool addOutput  (

}

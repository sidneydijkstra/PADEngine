/// @file logger.h
/// @brief Standalone header providing logging functionality.
/// @author Sander Albers
/// @version 1.0.0
/// @date 08/01/2020

#ifndef PAD_ENGINE_UTILITY_LOGGING_HEADER
#define PAD_ENGINE_UTILITY_LOGGING_HEADER

#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace pad {

/// @brief Enumeration specifying the severity of a log message.
enum class Level {
    DEBUG, INFO, WARNING, SEVERE, SIDNEYS_SECRET_LOG_LEVEL = 42069
};

/// @brief Class describing a Logger object, which may be used to log messages.
class Logger final {

public:

    /// The name of the default Logger object. Use this name to retrieve a
    /// general purpose Logger object with <tt>Logger::getLogger()</tt>
    inline static const std::string default_logger_name = "PAD_ENGINE";

    /// @brief Gets the Logger with the given name and creates it if it doesn't exist.
    /// @param loggerName The name of the logger to retrieve. Defaults to <tt>default_logger_name</tt>.
    /// @return A reference to the logger with the given name.
    inline static Logger& getLogger(const std::string& loggerName = default_logger_name) noexcept {
        static std::map<std::string, Logger*> loggers{};

        // Return the logger if it exists, otherwise create it first.
        if (auto lowerbound = loggers.lower_bound(loggerName);
            lowerbound != loggers.end() && !loggers.key_comp()(loggerName, lowerbound->first)) {
            return *(lowerbound->second);
        } else {
            Logger* logger = new Logger(loggerName);
            loggers.insert(lowerbound, std::make_pair(loggerName, logger));
            
            return *logger;
        }
    }

    /// @brief Sets an optional log file to be written to whenever a message is logged.
    /// @param fileName The name of the file to write to.
    inline void setLogFile(const std::string& fileName) {
        if (m_logFile.is_open()) m_logFile.close();
        m_logFile.open(fileName);
    }

    /// @brief Logs a message to the console and the log file if it was set.
    /// @param message The message to log.
    template<typename T>
    void log(const T& message) {
        this->log(Level::INFO, message);
    }

    /// @brief Logs a message to the console and the log file if it was set.
    /// @param level The severity of the message to log.
    /// @param message The message to log.
    template<typename T>
    void log(Level level, const T& message) {
        this->log(std::cout, level, message);
        if (m_logFile.is_open()) this->log(m_logFile, level, message);
    }
    
    /// @brief If debugging is enabled, logs a message to the console and the log file if it was set.
    /// @param message The message to log.
    template<typename T>
    void debug(const T& message) {
        if constexpr (debugging_enabled) this->log(Level::DEBUG, message);
    }

private:

#ifdef NDEBUG
    static constexpr bool debugging_enabled = false;
#else
    static constexpr bool debugging_enabled = true;
#endif

    std::string m_name;
    std::ofstream m_logFile;

    /// @brief Constructs a new Logger object with the given name.
    ///
    /// The internal constructor of a Logger object. This constructor
    /// was made private in favor of the 'multiton' pattern and should
    /// only be called by <tt>Logger::getLogger</tt>. If you wish to instantiate
    /// a new Logger object, you should use that method instead.
    ///
    /// The 'multiton' pattern is similar to the 'singleton' pattern,
    /// except that instead of only one instance, multiple instance are allowed.
    /// Each instance has it's own identifier, in this case a string. This allows
    /// for easy and global access to every existing Logger object.
    ///
    /// @param name The name of the logger.
    inline Logger(const std::string& name) noexcept : m_name(name) {
        // Empty.
    }

    /// @brief Logs a message to the given output stream.
    /// @param out The output stream to write the message to.
    /// @param level The severity of the message to log.
    /// @param message The message to log.
    template<typename T>
    void log(std::ostream& out, Level level, const T& message) {
        out << Logger::getCurrentTimeStamp()
            << " [" << m_name << "] [" << levelToString(level) << "]\t"
            << message << '\n';
    }

    /// @brief Gets the current time formatted as "YYYY-MM-DD hh:mm:ss".
    ///
    /// Gets the current time and formats it as a string following the
    /// "year-month-day time" format. This method was made, because as
    /// of now (C++17) there are no straightforward means to print a date.
    /// C++20 shows a more promising DateTime library, eliminating the need
    /// for this method.
    ///
    /// Note: <tt>std::localtime</tt> may warn that <tt>std::localtime</tt> is deprecated
    /// and should be replaced with <tt>std::localtime_s</tt>. This was not done however,
    /// as <tt>std::localtime_s</tt> may not be available on some platforms.
    ///
    /// @return The current time formatted as "YYYY-MM-DD hh:mm:ss".
    inline static std::string getCurrentTimeStamp() noexcept {
        // Create a new string and allocate enough bytes for
        // the timestamp (YYYY-MM-DD hh:mm:ss, 19 in total). 
        std::string timestamp(19, ' ');

        const auto cur_time = std::time(nullptr);
        std::strftime(timestamp.data(), timestamp.capacity(), "%F %T", std::localtime(&cur_time));

        return timestamp;
    }
   
    /// @brief Converts a Log Level to it's corresponding string.
    /// @return The Log Level as a string.
    inline static const char* levelToString(const Level level) {
        static const char* level_name[] = {
            "DEBUG", "INFO", "WARNING", "SEVERE"
        };

        return (level != Level::SIDNEYS_SECRET_LOG_LEVEL) ? level_name[static_cast<uint8_t>(level)] : "42069";
    }

    /// The default destructor of a Logger object. Made private
    /// to avoid external destruction of a Logger object, and therefore
    /// also the external construction of a Logger object.
    inline ~Logger(void) = default;

};

}

/* Temporary using-directive. Remove when the whole engine uses the same namespace. */
using namespace pad;

#endif

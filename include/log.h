#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <iostream>
#include <sstream>

class Log {
    private:
        static bool debug_mode_;
        Log () {};
        ~Log () {};
    public:
        static Log& getInstance () {
            static Log* instance_ = 0;
            if (!instance_) instance_ = new Log();
            return *instance_;
        }
        static void setDebugMode (bool debug_mode) {
            debug_mode_ = debug_mode;
        }
        void debug (std::string message) {
            if (debug_mode_) {
                message = "DEBUG: " + message + "\n";
                std::cout << message;
            }
        }
        void debug (std::ostringstream &message) {
            debug (message.str());
        }
        void info (std::string message) {
            message = "INFO:  " + message + "\n";
            std::cout << message;
        }
        void info (std::ostringstream &message) {
            info (message.str());
        }
        void error (std::string message) {
            message = "ERROR: " + message + "\n";
            std::cout << message;
        }
        void error (std::ostringstream &message) {
            error (message.str());
        }
};

#endif

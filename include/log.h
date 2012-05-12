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
            if (debug_mode_)
                std::cout << "DEBUG: " << message << std::endl;
        }
        void debug (std::stringstream &message) {
            debug (message.str());
        }
        void info (std::string message) {
            std::cout << "INFO:  " << message << std::endl;
        }
        void info (std::stringstream &message) {
            info (message.str());
        }
        void error (std::string message) {
            std::cout << "ERROR: " << message << std::endl;
        }
        void error (std::stringstream &message) {
            error (message.str());
        }
};

#endif

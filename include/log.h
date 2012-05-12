#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <iostream>

class Log {
    private:
        static Log* instance_;
        static bool debug_mode_;
        Log () {};
        ~Log () {};
    public:
        static Log& getInstance () {
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
        void error (std::string message) {
            std::cout << "ERROR: " << message << std::endl;
        }
};

#endif

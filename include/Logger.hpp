#pragma once
#include <string>

class Logger {
    std::string logFile;   // log file name
public:
    explicit Logger(const std::string& file = "deltafm.log");
    void log(const std::string& message);
};
#pragma once

#include <string>

class Logger {
    std::string logFile;

public:
    explicit Logger(const std::string& file = "deltafm.log");
    bool log(const std::string& message = "Unknown operation");
};

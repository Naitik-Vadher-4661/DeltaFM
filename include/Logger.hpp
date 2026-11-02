#pragma once
#include "Fileitem.hpp"
#include <string>

class Logger {
    fs::path p;
public:
    Logger();
    void Log(std::string);

};

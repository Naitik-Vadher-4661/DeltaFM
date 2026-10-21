#pragma once
#include "Fileitem.hpp"

#include <filesystem>
namespace fs=std::filesystem;
#include <string>

class Logger {

    Fileitem logfile;


public:
    Logger(fs::path logpath);
    void Log(std::string&,fs::file_time_type);

};

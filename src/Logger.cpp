#include "../include/Logger.hpp"
#include <filesystem>

#include <chrono>
#include <format>
#include <fstream>
// #include <iomanip>


Logger::Logger(fs::path logpath):logfile(logpath){}

void Logger::Log(std::string& msg,fs::file_time_type ft ) {

   std::ofstream out( logfile.getpath());

   std::string modtime=std::format("{:%Y-%m-%d %H:%M}", ft);

   out<<modtime<<" : "<<msg<<std::endl;
}

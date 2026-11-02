#include "../include/Logger.hpp"
#include <filesystem>

#include <chrono>
#include <format>
#include <fstream>



Logger::Logger(){
    p=fs::path(PROJECT_ROOT) / "logs"/"Deltalogs.txt";
    fs::create_directories(p.parent_path());
}

void Logger::Log(std::string msg) {
   fs::create_directories(p.parent_path());
   fs::file_time_type time = fs::file_time_type::clock::now();
   time=time+std::chrono::hours(5)+std::chrono::minutes(30);
   std::string modtime=std::format("{:%Y-%m-%d %H:%M}",time);
   std::ofstream f1( p,std::ios::app);
   f1<<modtime<<" : "<<msg<<std::endl;

}

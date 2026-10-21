#include "../include/Logger.hpp"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>

Logger::Logger(const std::string& file) : logFile(file) {}

bool Logger::log(const std::string& message) {
    std::ofstream out(logFile, std::ios::app);
    if (!out) return false;

    std::time_t t = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    std::tm tm = *std::localtime(&t);

    out << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " | "
        << (message.empty() ? "Unknown operation" : message) << '\n';
    return true;
}

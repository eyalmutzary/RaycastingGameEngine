#include "Logger.h"

Logger::Logger(const char* filePath) {
    file.open(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
    }
}

Logger::~Logger() {
    std::cout << "closed file" << std::endl;
    if (file.is_open()) {
        file.close();
    }
}

void Logger::log(const std::string& message) {
    if (file.is_open()) {
        file << message << std::endl;
    } else {
        std::cerr << "Log file is not open. Unable to log the message." << std::endl;
    }
}
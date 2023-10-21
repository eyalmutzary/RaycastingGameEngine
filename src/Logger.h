#ifndef RAYCASTING_LOGGER_H
#define RAYCASTING_LOGGER_H

#include <iostream>
#include <fstream>


class Logger {
public:
    explicit Logger(const char* filePath);

    void log(const std::string& message);

    ~Logger();

private:
    std::ofstream file;
};

#endif //RAYCASTING_LOGGER_H

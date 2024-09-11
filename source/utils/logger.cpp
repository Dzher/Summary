#include "logger.h"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace utils;

std::string Logger::getCurrentDate()
{
    std::time_t current_time = std::time(nullptr);
    std::tm* now_tm = std::localtime(&current_time);

    char date_buffer[11];
    std::strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d", now_tm);

    return std::string(date_buffer);
}

bool Logger::log(const std::string& filename, const std::string& content, LogMethod method)
{
    switch (method)
    {
        case LogMethod::Replace:
            return replaceFile(filename, content);
        case LogMethod::Append:
            return appendFile(filename, content);
        case LogMethod::Update:
            return updateFile(filename, content);
    }
}

bool Logger::replaceFile(const std::string& filename, const std::string& content)
{
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        file << content << std::endl;
        file.close();
        return true;
    }

    std::cerr << "Unable to open file: " << filename << std::endl;
    return false;
}

bool Logger::appendFile(const std::string& filename, const std::string& content)
{
    std::ofstream file(filename, std::ios_base::app);
    if (file.is_open())
    {
        file << content << std::endl;
        file.close();
        return true;
    }

    std::cerr << "Unable to open file: " << filename << std::endl;
    return false;
}

bool Logger::updateFile(const std::string& filename, const std::string& content)
{
    // TODO：Complete this later
    std::ofstream file(filename, std::ios_base::app);
    if (file.is_open())
    {
        file << content << std::endl;
        file.close();
        return true;
    }

    std::cerr << "Unable to open file: " << filename << std::endl;
    return false;
}

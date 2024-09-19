#include "logger.h"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace utils;

std::string Timmer::getCurrentDate()
{
    auto today = std::chrono::system_clock::now();
    return formatDate(today);
}

std::vector<std::string> Timmer::getLastNDates(int n)
{
    std::vector<std::string> dates;

    auto today = std::chrono::system_clock::now();

    for (int count = 0; count < n; ++count)
    {
        auto time_point = today - std::chrono::hours(24 * count);
        dates.insert(dates.begin(), formatDate(time_point));
    }

    return dates;
}

std::string Timmer::formatDate(const std::chrono::system_clock::time_point& time_point)
{
    std::time_t time = std::chrono::system_clock::to_time_t(time_point);

    // yyyy-mm-dd is sum of 10 characters, and + 1 the end character '\n'
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&time));

    return std::string(buffer);
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
    // TODO: Complete this later
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

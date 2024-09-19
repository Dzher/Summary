#ifndef _UTILS_LOGGER_H_
#define _UTILS_LOGGER_H_

#include <list>
#include <string>

namespace utils
{

enum class LogMethod
{
    Replace,
    Append,
    Update
};

class Timmer
{
public:
    static std::string getCurrentDate();
    static std::list<std::string> getLastNDates(int n);

private:
    static std::string formatDate(const std::chrono::system_clock::time_point& time_point);
};
class Logger
{
public:
    static bool log(const std::string& filename, const std::string& content, LogMethod method);
    // static std::string getLogPath();
    // static bool setLogPath(const std::string& path);

private:
    static bool replaceFile(const std::string& filename, const std::string& content);
    static bool appendFile(const std::string& filename, const std::string& content);
    static bool updateFile(const std::string& filename, const std::string& content);
};
} // namespace utils

#endif
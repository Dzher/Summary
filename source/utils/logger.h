#ifndef _UTILS_LOGGER_H_
#define _UTILS_LOGGER_H_

#include <string>

namespace utils
{

enum class LogMethod
{
    Replace,
    Append,
    Update
};

class Logger
{
public:
    static std::string getCurrentDate();
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
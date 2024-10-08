#ifndef _SUMMARY_TOOLS_CONFIG_HELPER_H_
#define _SUMMARY_TOOLS_CONFIG_HELPER_H_

#include <config.h>
#include <list>
#include <string>
#include <string_view>
#include "toml.hpp"

namespace tools
{

class ConfigHelper
{
    friend class PathHelper;

public:
    // template <typename ValueType>
    static void setSetting(const std::string& key, const std::string& value);
    static void setSetting(const std::string& key, const int value);
    static void setSetting(const std::string& key, const double value);

    static std::string getSetting(const std::string& key);
    static bool existSetting(const std::string& key);
    static bool existConfigFile();

    static void initConfigFile();
    static std::string generateKeyPath(std::list<std::string> key_list);

private:
    static std::string getOrCreateConfigFile();
    static void saveConfigFile(const toml::table& config_tbl);

public:
    static constexpr std::string_view kSummaryConfigPath{SUMMARY_CONFIG_PATH};
    static constexpr std::string kSummaryConfigFile{"summary.toml"};

    static constexpr std::string kSummary{"summary"};
    static constexpr std::string kMainPanel{"mainpanel"};
    static constexpr std::string kKeyCounter{"keycounter"};

    static constexpr std::string kSuffixLast{"last"};
    static constexpr std::string kSuffixOrigin{"origin"};
    static constexpr std::string kGeomtrySize{"geomtry"};
    static constexpr std::string kLogFilePath{"logFilePath"};
    static constexpr std::string kLogFileSize{"logFileSize"};
    static constexpr std::string kLogFileFrequency{"logFileFrequency"};
    static constexpr std::string kRunBackground{"runbackground"};
};
} // namespace tools

#endif
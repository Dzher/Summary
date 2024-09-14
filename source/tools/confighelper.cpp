#include "confighelper.h"
#include <filesystem>

using namespace tools;

void ConfigHelper::setSetting(const std::string& key, const std::string& value)
{
    auto config_file = getOrCreateConfigFile();
    if (config_file.empty())
    {
        return;
    }    
}

std::string ConfigHelper::getOrCreateConfigFile()
{
    auto config_file = std::string(kSummaryConfigPath) + std::string(kSummaryConfigFile);
    if (!std::filesystem::exists(config_file))
    {
        if (std::filesystem::create_directory(config_file))
        {
            return config_file;
        }
    }
    return config_file;
}
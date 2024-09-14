#include "confighelper.h"
#include "toml.hpp"

#include <filesystem>

using namespace tools;

void ConfigHelper::setSetting(const std::string& key, const std::string& value)
{
    auto config_file = getOrCreateConfigFile();
    if (config_file.empty())
    {
        return;
    }

    toml::table config = toml::parse_file(config_file);
    config.insert_or_assign(key, value);
}

void ConfigHelper::setSetting(const std::string& key, const int value)
{
    auto config_file = getOrCreateConfigFile();
    if (config_file.empty())
    {
        return;
    }

    toml::table config = toml::parse_file(config_file);
    config.insert_or_assign(key, value);
}

void ConfigHelper::setSetting(const std::string& key, const double value)
{
    auto config_file = getOrCreateConfigFile();
    if (config_file.empty())
    {
        return;
    }

    toml::table config = toml::parse_file(config_file);
    config.insert_or_assign(key, value);
}

std::string ConfigHelper::getSetting(const std::string& key)
{
    auto config_file = getOrCreateConfigFile();
    if (config_file.empty())
    {
        return "";
    }

    toml::table config = toml::parse_file(config_file);
    return config.at_path(key).value_or("");
}

bool ConfigHelper::existSetting(const std::string& key)
{
    auto config_file = getOrCreateConfigFile();
    if (config_file.empty())
    {
        return false;
    }

    toml::table config = toml::parse_file(config_file);
    return config.contains(key);
}

std::string ConfigHelper::getOrCreateConfigFile()
{
    auto config_file = std::string(kSummaryConfigPath) + kSummaryConfigFile;
    if (!std::filesystem::exists(config_file))
    {
        if (std::filesystem::create_directory(config_file))
        {
            return config_file;
        }
    }
    return config_file;
}

std::string ConfigHelper::generateKeyPath(std::list<std::string> key_list)
{
    std::string key_path;
    for (auto& key : key_list)
    {
        key_path += key;
        if (key != *key_list.end())
        {
            key_path += '.';
        }
    }
    return key_path;
}
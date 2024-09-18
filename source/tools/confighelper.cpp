#include "confighelper.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include "toml.hpp"

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

    saveConfigFile(config);
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

    saveConfigFile(config);
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

    saveConfigFile(config);
}

std::string ConfigHelper::getSetting(const std::string& key)
{
    auto config_file = getOrCreateConfigFile();
    if (config_file.empty())
    {
        return "";
    }

    toml::table config = toml::parse_file(config_file);
    return config.at_path(key).value<std::string>().value_or("");
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

bool ConfigHelper::existConfigFile()
{
    auto config_file_path = std::string(kSummaryConfigPath) + kSummaryConfigFile;
    return std::filesystem::exists(config_file_path);
}

std::string ConfigHelper::getOrCreateConfigFile()
{
    auto config_file_path = std::string(kSummaryConfigPath) + kSummaryConfigFile;
    if (!std::filesystem::exists(config_file_path))
    {
        std::filesystem::create_directories(kSummaryConfigPath);
        std::ofstream config_file(config_file_path, std::ios::out | std::ios::trunc);
    }
    return config_file_path;
}

std::string ConfigHelper::generateKeyPath(std::list<std::string> key_list)
{
    std::string key_path;
    for (auto& key : key_list)
    {
        key_path += key;
        if (key != *(--key_list.end()))
        {
            key_path += '.';
        }
    }
    return key_path;
}

void ConfigHelper::initConfigFile()
{
    auto config_tbl = toml::table{
        {"author",
         toml::table{
             {"name", "Dzher"},
             {"github", "https://github.com/Dzher"},
         }},
        {kSummary,
         toml::table{
             {"config", "Default Configuration"},
             {"repo", "https://github.com/Dzher/Summary"},
             {"version", "0.0.1"},
         }},
        {kMainPanel,
         toml::table{
             {kGeomtrySize, ""},
             {kRunBackground, true},
         }},
        {kKeyCounter,
         toml::table{
             {kGeomtrySize, ""},
             {kLogFilePath, "../keycounter/logs/"},
             {kLogFileSize, 100},
             {kLogFileFrequency, 5},
             {kRunBackground, true},
         }},
    };

    saveConfigFile(config_tbl);
}

void ConfigHelper::saveConfigFile(const toml::table& config_tbl)
{
    std::ofstream config_file(getOrCreateConfigFile(), std::ios::out | std::ios::trunc);
    // TODO: consider multi threads write issue.
    // std::lock_guard<mutex_>
    config_file << toml::toml_formatter(config_tbl, toml::format_flags::none);
    config_file.flush();
    config_file.close();
}
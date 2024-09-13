#ifndef _SUMMARY_TOOLS_PATH_HELPER_H_
#define _SUMMARY_TOOLS_PATH_HELPER_H_

#include <QString>

namespace tools
{

enum class ResourceType
{
    Image,
    Config,
    Theme,
    Font,
    Message,
    Language,
    Doc
};

class PathHelper
{
public:
    static QString getResourcePath(ResourceType type, const QString& file_name, const QString& group = "");
    static QString getImagePath(const QString& file_name, const QString& group);
    static QString getConfigPath(const QString& file_name);
    static QString getThemePath(const QString& file_name);
    static QString getFontPath(const QString& file_name);
    static QString getMessagePath(const QString& file_name);
    static QString getLanguagePath(const QString& file_name);
    static QString getDocPath(const QString& file_name);

private:
    static QString getResourceRootPath();
};

} // namespace tools

#endif
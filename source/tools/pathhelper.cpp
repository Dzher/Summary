#include "pathhelper.h"

#include <QtCore/QFile>
#include <iostream>

#include "config.h"

using namespace tools;

QString PathHelper::getResourcePath(ResourceType type, const QString& file_name, const QString& group)
{
    QString resource_path;
    QString root_path = getResourceRootPath();

    switch (type)
    {
        case ResourceType::Image:
            if (group.isEmpty())
            {
                resource_path = QString("%1/images/%2").arg(resource_path).arg(file_name);
            }
            else
            {
                resource_path = QString("%1/images/%2/%3").arg(resource_path).arg(group).arg(file_name);
            }
            break;
        case ResourceType::Config:
            resource_path = QString("%1/config/%2").arg(resource_path).arg(file_name);
            break;
        case ResourceType::Theme:
            resource_path = QString("%1/theme/%2").arg(resource_path).arg(file_name);
            break;
        case ResourceType::Font:
            resource_path = QString("%1/font/%2").arg(resource_path).arg(file_name);
            break;
        case ResourceType::Message:
            resource_path = QString("%1/message/%2").arg(resource_path).arg(file_name);
            break;
        case ResourceType::Language:
            resource_path = QString("%1/language/%2").arg(resource_path).arg(file_name);
            break;
        case ResourceType::Doc:
            resource_path = QString("%1/docs/%2").arg(resource_path).arg(file_name);
            break;
    }

    if (QFile::exists(resource_path))
    {
        return resource_path;
    }
    return {};
}

QString PathHelper::getResourceRootPath()
{
    const char* project_root_path = RESOURCE_ROOT;
    if (project_root_path)
    {
        return QString(project_root_path);
    }

    std::cerr << "RESOURCE_ROOT env variable is not set" << std::endl;
    return "";
}

QString PathHelper::getImagePath(const QString& file_name, const QString& group)
{
    return getResourcePath(ResourceType::Image, file_name, group);
}

QString PathHelper::getConfigPath(const QString& file_name)
{
    return getResourcePath(ResourceType::Config, file_name);
}

QString PathHelper::getThemePath(const QString& file_name)
{
    return getResourcePath(ResourceType::Theme, file_name);
}

QString PathHelper::getFontPath(const QString& file_name)
{
    return getResourcePath(ResourceType::Font, file_name);
}

QString PathHelper::getMessagePath(const QString& file_name)
{
    return getResourcePath(ResourceType::Message, file_name);
}

QString PathHelper::getLanguagePath(const QString& file_name)
{
    return getResourcePath(ResourceType::Language, file_name);
}

QString PathHelper::getDocPath(const QString& file_name)
{
    return getResourcePath(ResourceType::Doc, file_name);
}
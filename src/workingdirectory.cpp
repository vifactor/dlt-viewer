#include "workingdirectory.h"

#include "qdltsettingsmanager.h"

// See workingdirectory.h for documentation.

WorkingDirectory::WorkingDirectory(const QString &path) : m_workDirPath(path)
{
}

QString WorkingDirectory::createKeyFor(WorkingDirectoryType type, QString extra)
{
    QString key = "WorkingDirectory/";
    switch(type)
    {
    case WorkingDirectory::LogFile:
        key += "LogFile";
        break;
    case WorkingDirectory::ProjectFile:
        key += "ProjectFile";
        break;
    case WorkingDirectory::FilterFile:
        key += "FilterFile";
        break;
    case WorkingDirectory::ExportDir:
        key += "FilterDir";
        break;
    case WorkingDirectory::PluginConfig:
        key += "Plugin";
        key += extra;
        break;
    }
    return key;
}

// The meat of getters
QString WorkingDirectory::getDirectory(WorkingDirectoryType type, QString extra)
{
    /**
     * By default, empty string is returned. This should be
     * fine for all platforms:
     * Windows -- Application directory
     * Linux   -- Home Directory
     * Mac     -- ???
     **/

    if (!m_workDirPath.isEmpty())
    {
        return m_workDirPath;
    }

    QString key = createKeyFor(type, extra);
    QString defaultValue = (type == WorkingDirectory::PluginConfig) ? "plugins/" : "./";
    return QDltSettingsManager::getInstance()->value(key, defaultValue).toString();
}

// The meat of setters
void WorkingDirectory::setDirectory(WorkingDirectoryType type, QString dir, QString extra)
{
    QString key = createKeyFor(type, extra);
    QDltSettingsManager::getInstance()->setValue(key, dir);
}

// Getters
QString WorkingDirectory::getDltDirectory()
{ return getDirectory(LogFile); }
QString WorkingDirectory::getDlpDirectory()
{ return getDirectory(ProjectFile); }
QString WorkingDirectory::getDlfDirectory()
{ return getDirectory(FilterFile); }
QString WorkingDirectory::getExportDirectory()
{ return getDirectory(ExportDir); }
QString WorkingDirectory::getPluginDirectory(QString pluginName)
{ return getDirectory(PluginConfig, pluginName); }

// Setters
void WorkingDirectory::setDltDirectory(QString dir)
{ setDirectory(LogFile, dir); }
void WorkingDirectory::setDlpDirectory(QString dir)
{ setDirectory(ProjectFile, dir); }
void WorkingDirectory::setDlfDirectory(QString dir)
{ setDirectory(FilterFile, dir); }
void WorkingDirectory::setExportDirectory(QString dir)
{ setDirectory(ExportDir, dir); }
void WorkingDirectory::setPluginDirectory(QString pluginName, QString dir)
{ setDirectory(PluginConfig, dir, pluginName); }

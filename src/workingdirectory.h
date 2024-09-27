#ifndef WORKINGDIRERCTORY_H
#define WORKINGDIRERCTORY_H

#include <QString>

/*!
* \brief The WorkingDirerctory class
* This is a convenience class to access the different working directories
* stored in the config.ini of the viewer. The config.ini is accessed through
* QDltSettingsManager.
*\sa QDltSettingsManager
*/
class WorkingDirectory
{
public:
    enum WorkingDirectoryType {
        LogFile,
        ProjectFile,
        FilterFile,
        ExportDir,
        PluginConfig
    };

public:
    WorkingDirectory();

    //! Get working directory for DLT files
    QString getDltDirectory();
    //! Get working directory for Project files
    QString getDlpDirectory();
    //! Get working directory for Filter files
    QString getDlfDirectory();
    //! Get working directory for export files
    QString getExportDirectory();
    //! Get working directory for plugin configuration
    QString getPluginDirectory(QString pluginName);

    //! Set working directory for DLT files
    void setDltDirectory(QString dir);
    //! Set working directory for Project files
    void setDlpDirectory(QString dir);
    //! Set working directory for Filter files
    void setDlfDirectory(QString dir);
    //! Set working directory for export files
    void setExportDirectory(QString dir);
    //! Set working directory for plugin configuration
    void setPluginDirectory(QString pluginName, QString dir);

    // Helpers
private:
    QString createKeyFor(WorkingDirectoryType type, QString extra);
    /*!
     * \brief getDirectory
     * Get working directory for specific type of operation.
     * \param type Type of operation defined in WorkingDirectoryType
     * \param extra Optional parameter. Used for getting settings for a plugin
     * \return Current working directory for the operation
     * \sa WorkingDirectoryType
     */
    QString getDirectory(WorkingDirectoryType type, QString extra = QString());

    /*!
     * \brief setDirectory
     * Set directory for specific type of operation.
     * \param type The type defined by WorkingDirectoryType.
     * \param extra Possible plugin name.
     * \sa WorkingDirectoryType
     */
    void setDirectory(WorkingDirectoryType type, QString dir, QString extra = QString());


};

#endif // WORKINGDIRERCTORY_H

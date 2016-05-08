/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDir>
#include <QSettings>

class Settings
{
public:
    Settings();

    void setLastOpenDir(const QDir &dir);
    QDir lastOpenDir() const;

    void setLastOpenedFiles(const QStringList &files);
    QStringList lastOpenedFiles() const;

private:
    QSettings m_settings;
};

#endif // SETTINGS_H

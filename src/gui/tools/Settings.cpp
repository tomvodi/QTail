/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */
#include "Settings.h"

#include <QCoreApplication>

static const QString LastOpenDirValueName("last open dir");
static const QString LastOpenFilesValueName("last open files");

Settings::Settings()
{
}

void Settings::setLastOpenDir(const QDir &dir)
{
   m_settings.setValue(LastOpenDirValueName, dir.absolutePath());
}

QDir Settings::lastOpenDir() const
{
   return QDir(m_settings.value(LastOpenDirValueName).toString(), QCoreApplication::applicationDirPath());
}

void Settings::setLastOpenedFiles(const QStringList &files)
{
   m_settings.setValue(LastOpenFilesValueName, files);
}

/*!
 * \brief Settings::lastOpenFiles
 * A list of the files that were opened the last time the application was started.
 */
QStringList Settings::lastOpenedFiles() const
{
   return m_settings.value(LastOpenFilesValueName).toStringList();
}

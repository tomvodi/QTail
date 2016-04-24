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

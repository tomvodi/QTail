/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/FileWatcherInterface.h"

FileWatcherInterface::FileWatcherInterface(QObject *parent)
   : QObject(parent)
{
}

void FileWatcherInterface::setFilePath(const QString &filePath)
{
   m_filePath = filePath;
}

QString FileWatcherInterface::filePath() const
{
   return m_filePath;
}

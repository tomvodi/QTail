/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "MocFileWatcher.h"

MocFileWatcher::MocFileWatcher(QObject *parent)
   : FileWatcherInterface(parent)
{
}

void MocFileWatcher::setFilePath(const QString &filePath)
{
   FileWatcherInterface::setFilePath(filePath);
}

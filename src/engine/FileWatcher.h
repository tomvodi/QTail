/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QFileInfo>
#include "include/FileWatcherInterface.h"

class QFileSystemWatcher;

class FileWatcher : public FileWatcherInterface
{
   Q_OBJECT
public:
   explicit FileWatcher(QObject *parent = 0);

   void setFilePath(const QString &filePath);

private slots:
   void fileHasChanged();

private:
   void createConnections();
   QFileSystemWatcher *m_fileSystemWatcher;
   QFileInfo m_fileInfo;
};

#endif // FILEWATCHER_H

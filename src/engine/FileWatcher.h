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
   friend class FileWatcherTest;

public:
   explicit FileWatcher(QObject *parent = 0);
   ~FileWatcher();

   void setFilePath(const QString &filePath) override;
   void setUpdateInterval(int updateInterval) override;

protected:
   void timerEvent(QTimerEvent *event);

private slots:
   void fileHasChanged();

private:
   void createConnections();
   QFileSystemWatcher *m_fileSystemWatcher;
   QFileInfo m_fileInfo;
   int m_timerId = 0;
};

#endif // FILEWATCHER_H

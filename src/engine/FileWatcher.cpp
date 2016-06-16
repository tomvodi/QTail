/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDebug>
#include <QTimerEvent>

#include <QFileSystemWatcher>
#include <QFileInfo>

#include "FileWatcher.h"

static const int FileCheckInterval(500);

FileWatcher::FileWatcher(QObject *parent)
   : FileWatcherInterface(parent),
     m_fileSystemWatcher(new QFileSystemWatcher(this))
{
   createConnections();
}

FileWatcher::~FileWatcher()
{
   if (m_timerId > 0) {
      killTimer(m_timerId);
      m_timerId = 0;
   }
}

void FileWatcher::createConnections()
{
}

void FileWatcher::setFilePath(const QString &filePath)
{
   FileWatcherInterface::setFilePath(filePath);

   if (m_fileSystemWatcher->files().count() ||
       filePath.isEmpty() ||
       !QFile::exists(filePath)) {
      return;
   }

   m_fileSystemWatcher->addPath(filePath);
   m_fileInfo.setFile(filePath);

   // Read a file info value once, so that the file info cache is populated
   // with the actual informations.
   m_fileInfo.size();

   connect(m_fileSystemWatcher, &QFileSystemWatcher::fileChanged,
           this, &FileWatcher::fileHasChanged);

   m_timerId = startTimer(FileCheckInterval);
}

void FileWatcher::timerEvent(QTimerEvent *event)
{
   if (event->timerId() == m_timerId) {
      QFileInfo tempFileInfo(m_fileInfo.absoluteFilePath());
      qint64 oldSize = m_fileInfo.size();
      qint64 newSize = tempFileInfo.size();

      if (oldSize != newSize) {
         fileHasChanged();
      }
   }

   FileWatcherInterface::timerEvent(event);
}

void FileWatcher::fileHasChanged()
{
   if (m_fileInfo.fileName().isEmpty()) {
      return;
   }

   qint64 oldSize = m_fileInfo.size();
   m_fileInfo.refresh();

   if (!m_fileInfo.exists()) {
      emit fileRemoved();
      return;
   }

   qint64 newSize = m_fileInfo.size();
   if (newSize != oldSize) {
      emit sizeChanged(oldSize, newSize);
   }
}

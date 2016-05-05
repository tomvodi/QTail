/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <include/FileWatcherInterface.h>

#include <QTextStream>

#include "FileReadLogic.h"

FileReadLogic::FileReadLogic(QObject *parent)
   : QObject(parent),
     m_file(new QFile())
{

}

FileReadLogic::~FileReadLogic()
{
   delete m_file;
}

void FileReadLogic::sizeChanged(qint64 oldSize, qint64 newSize)
{
   Q_UNUSED(oldSize);
   Q_UNUSED(newSize);

   if (m_file->fileName().isEmpty()) {
      return;
   }

   if (!m_file->isOpen() &&
       !m_file->open(QIODevice::ReadOnly)) {
      return;
   }

   if (m_file->size() == 0) {
      return;
   }

   QTextStream stream(m_file);
   QStringList lines;
   while (!stream.atEnd()) {
      lines << stream.readLine();
   }

   emit fileCleared();
   emit linesAppended(lines);

   m_file->close();
}

void FileReadLogic::fileRemoved()
{

}

void FileReadLogic::setFileWatcher(FileWatcherInterface *fileWatcher)
{
   if (!m_fileWatcher.isNull()) {
      return;
   }

   m_file->setFileName(fileWatcher->filePath());
   m_fileWatcher = fileWatcher;

   connect(fileWatcher, &FileWatcherInterface::sizeChanged,
           this, &FileReadLogic::sizeChanged);
   connect(fileWatcher, &FileWatcherInterface::fileRemoved,
           this, &FileReadLogic::fileRemoved);

   sizeChanged(0, 0);
}

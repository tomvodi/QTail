/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <include/FileWatcherInterface.h>

#include <QTextStream>

#include "ReloadAppendLogic.h"

ReloadAppendLogic::ReloadAppendLogic(QObject *parent)
   : QObject(parent),
     m_file(new QFile())
{

}

ReloadAppendLogic::~ReloadAppendLogic()
{
   delete m_file;
}

void ReloadAppendLogic::sizeChanged(qint64 oldSize, qint64 newSize)
{
   Q_UNUSED(oldSize);
   Q_UNUSED(newSize);

   if (m_file->fileName().isEmpty()) {
      return;
   }

   if (!m_file->open(QIODevice::ReadOnly)) {
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

void ReloadAppendLogic::fileRemoved()
{

}

void ReloadAppendLogic::setFileWatcher(FileWatcherInterface *fileWatcher)
{
   if (!m_fileWatcher.isNull()) {
      return;
   }

   m_file->setFileName(fileWatcher->filePath());
   m_fileWatcher = fileWatcher;

   connect(fileWatcher, &FileWatcherInterface::sizeChanged,
           this, &ReloadAppendLogic::sizeChanged);
   connect(fileWatcher, &FileWatcherInterface::fileRemoved,
           this, &ReloadAppendLogic::fileRemoved);
}

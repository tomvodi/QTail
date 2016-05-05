/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <include/FileViewInterface.h>

#include <QTextStream>

#include "FileReadLogic.h"
#include "FileWatcher.h"
#include "TailEngine.h"

TailEngine::TailEngine(QObject *parent)
   : QObject(parent)
{

}

void TailEngine::addFiles(const QFileInfo &file, const FileViews &views)
{
   foreach (const FileView &view, views) {
      addFile(file, view);
   }
}

void TailEngine::addFile(const QFileInfo &file, const FileView &view)
{
   FileWatcher *fileWatcher = new FileWatcher(this);
   fileWatcher->setFilePath(file.absoluteFilePath());

   FileReadLogic *fileReadLogic = new FileReadLogic(this);
   fileReadLogic->setFileWatcher(fileWatcher);

   if (view->viewFeatures().testFlag(FileViewInterface::HasTextView)) {
      connect(fileReadLogic, &FileReadLogic::fileCleared,
              [view] { view->clearTextView(); });
      connect(fileReadLogic, &FileReadLogic::lineAppended,
              [view] (const QString &line) { view->appendLine(line); });
      connect(fileReadLogic, &FileReadLogic::linesAppended,
              [view] (const QStringList &lines) { view->appendLines(lines); });
   }

   connect(fileWatcher, &FileWatcher::sizeChanged,
           [this, file] (qint64 oldSize, qint64 newSize) {
      handleChangedFileSize(file, oldSize, newSize);
   });

   connect(fileWatcher, &FileWatcher::fileRemoved,
           [this, file] {
      handleRemovedFile(file);
   });

   FileContext context = fileContextOfFile(file);
   context.setFileInfo(file);
   context.addFileView(view);
   context.setFileWatcher(fileWatcher);
   context.setFileReadLogic(fileReadLogic);
   setFileContextOfFile(file, context);

   handleChangedFileContent(file);
}

void TailEngine::removeFile(const QFileInfo &file)
{

}

void TailEngine::reloadFile(const QFileInfo &file)
{

}

uint qHash(const QFileInfo &fileInfo)
{
   return qHash(fileInfo.absoluteFilePath());
}

void TailEngine::setFileContextOfFile(const QFileInfo &file, FileContext context)
{
   m_fileContexts.insert(file, context);
}

void TailEngine::handleChangedFileSize(const QFileInfo &file, qint64 oldSize, qint64 newSize)
{
   Q_UNUSED(oldSize);
   Q_UNUSED(newSize);
   FileContext context = fileContextOfFile(file);

   // Handle file state
   foreach (FileView view, context.fileViews()) {
      if (view->viewFeatures().testFlag(FileViewInterface::HasStateView)) {
         view->setFileState(FileState::FileHasChanged);
      }
   }
}

void TailEngine::handleChangedFileContent(const QFileInfo &file)
{
   FileContext context = fileContextOfFile(file);

   // Handle file content
   QFile textFile(file.absoluteFilePath());
   textFile.open(QIODevice::ReadOnly);
   QTextStream stream(&textFile);
   QStringList lines;
   while (!stream.atEnd()) {
      lines << stream.readLine();
   }

   foreach (FileView view, context.fileViews()) {
      if (view->viewFeatures().testFlag(FileViewInterface::HasTextView)) {
         view->clearTextView();
         view->appendLines(lines);
      }
   }
}

void TailEngine::handleRemovedFile(const QFileInfo &file)
{
   FileContext context = fileContextOfFile(file);

   // Handle file state
   foreach (FileView view, context.fileViews()) {
      if (view->viewFeatures().testFlag(FileViewInterface::HasStateView)) {
         view->setFileState(FileState::FileError);
      }
   }
}

TailEngine::FileContext TailEngine::fileContextOfFile(const QFileInfo &file)
{
   if (m_fileContexts.contains(file)) {
      return m_fileContexts.value(file);
   } else {
      m_fileContexts.insert(file, TailEngine::FileContext());
      return fileContextOfFile(file);
   }
}

QFileInfo TailEngine::FileContext::fileInfo() const
{
   return m_fileInfo;
}

void TailEngine::FileContext::setFileInfo(const QFileInfo &fileInfo)
{
   m_fileInfo = fileInfo;
}

FileWatcher *TailEngine::FileContext::fileWatcher() const
{
   return m_fileWatcher;
}

void TailEngine::FileContext::setFileWatcher(FileWatcher *fileWatcher)
{
   m_fileWatcher = fileWatcher;
}

FileViews TailEngine::FileContext::fileViews() const
{
   return m_fileViews;
}

void TailEngine::FileContext::setFileViews(const FileViews &fileViews)
{
   m_fileViews = fileViews;
}

void TailEngine::FileContext::addFileView(const FileView &fileView)
{
   m_fileViews << fileView;
}

FileReadLogic *TailEngine::FileContext::fileReadLogic() const
{
   return m_fileReadLogic;
}

void TailEngine::FileContext::setFileReadLogic(FileReadLogic *fileReadLogic)
{
   m_fileReadLogic = fileReadLogic;
}

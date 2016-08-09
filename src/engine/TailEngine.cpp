/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <include/FileViewInterface.h>
#include <include/FilterGroup.h>

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
   view->setFileInfo(file);

   FileWatcher *fileWatcher = new FileWatcher(this);
   fileWatcher->setFilePath(file.absoluteFilePath());
   fileWatcher->setUpdateInterval(m_textViewSettings.updateInterval());

   FileReadLogic *fileReadLogic = new FileReadLogic(this);
   if (view->viewFeatures().testFlag(FileViewInterface::HasTextView)) {
      connect(fileReadLogic, &FileReadLogic::fileCleared,
              [view] { view->clearTextView(); });
      connect(fileReadLogic, &FileReadLogic::linesAppended,
              [view] (const QStringList &lines) { view->appendLines(lines); });
      qint64 offsetSize = file.size();

      view->readCompleteFileUntil(offsetSize);
      fileWatcher->setSizeOffset(offsetSize);

      view->setTextViewSettings(m_textViewSettings);
   }
   fileReadLogic->setFileWatcher(fileWatcher);

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
}

void TailEngine::removeFile(const QFileInfo &file)
{
   if (!m_fileContexts.contains(file)) {
      return;
   }

   FileContext context = fileContextOfFile(file);
   delete context.fileWatcher();
   delete context.fileReadLogic();

   m_fileContexts.remove(file);
}

void TailEngine::setFileActive(const QFileInfo &file, bool active)
{
   if (!m_fileContexts.contains(file)) {
      return;
   }

   FileContext context = fileContextOfFile(file);

   // Handle file state
   foreach (FileView view, context.fileViews()) {
      view->setFileActive(active);
   }
}

void TailEngine::setTextViewSettings(const TextViewSettings &settings)
{
   m_textViewSettings = settings;

   foreach (const FileContext &fileContext, m_fileContexts) {
      if (fileContext.fileWatcher()) {
         fileContext.fileWatcher()->setUpdateInterval(settings.updateInterval());
      }

      foreach (const FileView &view, fileContext.fileViews()) {
         if (view->viewFeatures().testFlag(FileViewInterface::HasTextView)) {
            view->setTextViewSettings(settings);
         }
      }
   }
}

void TailEngine::setTextViewFont(const QFont &font)
{
   m_textViewFont = font;

   foreach (const FileContext &fileContext, m_fileContexts) {
      foreach (const FileView &view, fileContext.fileViews()) {
         if (view->viewFeatures().testFlag(FileViewInterface::HasTextView)) {
            view->setTextViewFont(font);
         }
      }
   }
}

/*!
 * \brief TailEngine::setFilterGroupsForFile
 * Set filter groups for a file. This results in:
 *  - set filter groups in file view
 *  - trigger a complete read of the file in view
 * \param file
 * \param filterGroups
 */
void TailEngine::setActiveFiltersForFile(const QFileInfo &file, const QList<FilterRule> &filters)
{
   FileContext context = fileContextOfFile(file);
   foreach (FileView fileView, context.fileViews()) {
      if (fileView->viewFeatures().testFlag(FileViewInterface::HasTextView)) {
         QFileInfo fileInfo = context.fileInfo();
         fileInfo.refresh();
         qint64 sizeOffset = fileInfo.size();

         fileView->setActiveFilters(filters);
         fileView->readCompleteFileUntil(sizeOffset);
         context.fileWatcher()->setSizeOffset(sizeOffset);
      }
   }

   setFileContextOfFile(file, context);
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

FileWatcherInterface *TailEngine::FileContext::fileWatcher() const
{
   return m_fileWatcher;
}

void TailEngine::FileContext::setFileWatcher(FileWatcherInterface *fileWatcher)
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

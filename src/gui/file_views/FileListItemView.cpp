/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "FileListItemWidget.h"
#include "FileListItemView.h"

FileListItemView::FileListItemView(QObject *parent)
   : FileViewInterface(parent),
     m_listWidget(new FileListItemWidget)
{
   connect(m_listWidget.data(), &FileListItemWidget::closeFileRequested,
           this, &FileListItemView::requestCloseFile);
}

FileListItemView::~FileListItemView()
{
   m_listWidget.clear();
}

FileViewInterface::Features FileListItemView::viewFeatures() const
{
   return FileViewInterface::HasStateView | FileViewInterface::HasTextView;
}

void FileListItemView::setFileState(FileState state)
{
   if (m_fileActive) {
      return;
   }

   m_listWidget->setFileState(state);
}

QPointer<QWidget> FileListItemView::widget() const
{
   return QPointer<QWidget>(m_listWidget);
}

void FileListItemView::setFileInfo(const QFileInfo &fileInfo)
{
   m_listWidget->setFileName(fileInfo.fileName());
}

void FileListItemView::setFileActive(bool active)
{
   m_fileActive = active;

   if (m_fileActive) {
      m_listWidget->setLineCount(0);
      m_listWidget->setFileState(FileState::FileInSync);
   }
}

void FileListItemView::appendLine(const QString &)
{
   if (m_fileActive) {
      return;
   }

   m_listWidget->addLineCount(1);
}

void FileListItemView::appendLines(const QStringList &lines)
{
   if (m_fileActive) {
      return;
   }

   m_listWidget->addLineCount(lines.count());
}

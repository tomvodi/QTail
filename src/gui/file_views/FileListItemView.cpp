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
   return FileViewInterface::HasStateView;
}

void FileListItemView::setFileState(FileState state)
{
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

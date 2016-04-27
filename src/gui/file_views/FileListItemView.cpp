/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "FileListItemWidget.h"
#include "FileListItemView.h"

FileListItemView::FileListItemView()
   : m_listWidget(new FileListItemWidget)
{
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

QPointer<FileListItemWidget> FileListItemView::listWidget() const
{
   return m_listWidget;
}


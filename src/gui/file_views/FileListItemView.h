/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILELISTITEMVIEW_H
#define FILELISTITEMVIEW_H

#include <QPointer>

#include <include/FileViewInterface.h>

class FileListItemWidget;

/*!
 * \brief The FileListItemView class
 * An interface implementation, that holds a FileListItemWidget.
 */
class FileListItemView : public FileViewInterface
{
public:
   FileListItemView();
   ~FileListItemView();

   // FileViewInterface interface
   FileViewInterface::Features viewFeatures() const override;
   void setFileState(FileState state) override;
   QPointer<QWidget> widget() const override;
   void setFileInfo(const QFileInfo &fileInfo) override;

private:
   QPointer<FileListItemWidget> m_listWidget;
};

#endif // FILELISTITEMVIEW_H

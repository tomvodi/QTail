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
   friend class FileListItemViewTest;

public:
   FileListItemView(QObject *parent=0);
   ~FileListItemView();

   // FileViewInterface interface
   FileViewInterface::Features viewFeatures() const override;
   void setFileState(FileState state) override;
   QPointer<QWidget> widget() const override;
   void setFileInfo(const QFileInfo &fileInfo) override;
   void setFileActive(bool active) override;

public slots:
   void appendLine(const QString &) override;
   void appendLines(const QStringList &lines) override;

private:
   QPointer<FileListItemWidget> m_listWidget;
   bool m_fileActive = false;
};

#endif // FILELISTITEMVIEW_H

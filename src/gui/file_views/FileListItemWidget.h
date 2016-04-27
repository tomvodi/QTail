/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */
#ifndef FILELISTITEMWIDGET_H
#define FILELISTITEMWIDGET_H

#include <QFrame>

#include <include/FileViewInterface.h>

namespace Ui {
class FileListItemWidget;
}

class FileListItemWidget : public QFrame

{
    Q_OBJECT
    friend class FileListItemWidgetTest;

public:
    explicit FileListItemWidget(QWidget *parent = 0);
    ~FileListItemWidget();

    void setFileName(const QString &fileName);
    QString fileName() const;
    void setLineCount(quint64 lineCount);

    void setFileState(FileState state);

    FileState fileState() const;

signals:
    void closeFileRequested();

private:
    Ui::FileListItemWidget *ui;
    FileState m_fileState;
};

#endif // FILELISTITEMWIDGET_H

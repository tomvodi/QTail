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

namespace Ui {
class FileListItemWidget;
}

class FileListItemWidget : public QFrame
{
    Q_OBJECT
    friend class FileListItemWidgetTest;

public:
    enum class FileState {
        FileError,
        FileInSync,
        FileHasNewLines
    };

    explicit FileListItemWidget(QWidget *parent = 0);
    ~FileListItemWidget();

    void setFileName(const QString &fileName);
    void setLineCount(quint64 lineCount);

    void setFileState(FileState state);

signals:
    void closeFileRequested();

private:
    Ui::FileListItemWidget *ui;
};

#endif // FILELISTITEMWIDGET_H

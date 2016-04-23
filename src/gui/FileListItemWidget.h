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

public:
    explicit FileListItemWidget(QWidget *parent = 0);
    ~FileListItemWidget();

private:
    Ui::FileListItemWidget *ui;
};

#endif // FILELISTITEMWIDGET_H

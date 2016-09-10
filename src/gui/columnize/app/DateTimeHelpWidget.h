/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef DATETIMEHELPWIDGET_H
#define DATETIMEHELPWIDGET_H

#include <QFrame>

namespace Ui {
class DateTimeHelpWidget;
}

class DateTimeHelpWidget : public QFrame
{
   Q_OBJECT

public:
   explicit DateTimeHelpWidget(QWidget *parent = 0);
   ~DateTimeHelpWidget();

private:
   Ui::DateTimeHelpWidget *ui;
};

#endif // DATETIMEHELPWIDGET_H

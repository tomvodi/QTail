/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef DATETIMECONFIGWIDGET_H
#define DATETIMECONFIGWIDGET_H

#include <QFrame>

namespace Ui {
class DateTimeConfigWidget;
}

class DateTimeConfigWidget : public QFrame
{
   Q_OBJECT

public:
   explicit DateTimeConfigWidget(QWidget *parent = 0);
   ~DateTimeConfigWidget();

private:
   Ui::DateTimeConfigWidget *ui;
};

#endif // DATETIMECONFIGWIDGET_H

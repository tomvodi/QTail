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
class QLabel;

class DateTimeConfigWidget : public QFrame
{
   Q_OBJECT

public:
   explicit DateTimeConfigWidget(QWidget *parent = 0);
   ~DateTimeConfigWidget();

private slots:
   void on_formatHelpButton_clicked();

private:
   Ui::DateTimeConfigWidget *ui;
   QLabel *m_formatHelpLabel;
   void initLocaleComboBox();
};

#endif // DATETIMECONFIGWIDGET_H

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
#include <QLocale>

namespace Ui {
class DateTimeConfigWidget;
}
class DateTimeHelpWidget;

class DateTimeConfigWidget : public QFrame
{
   friend class DateTimeConfigWidgetTest;
   Q_OBJECT

public:
   explicit DateTimeConfigWidget(QWidget *parent = 0);
   ~DateTimeConfigWidget();

   QLocale::Language currentSelectedLanguage() const;
   void setSelectedLanguage(const QLocale::Language language);

private slots:
   void on_formatHelpButton_clicked();
   void on_testStringLineEdit_textChanged();
   void on_formatLineEdit_textChanged();
   void on_testButton_clicked();

private:
   Ui::DateTimeConfigWidget *ui;
   DateTimeHelpWidget *m_formatHelpWidget;
   void initLocaleComboBox();
   void checkforEnabledTestButton();
};

#endif // DATETIMECONFIGWIDGET_H

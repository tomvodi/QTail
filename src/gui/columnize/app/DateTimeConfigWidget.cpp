/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "DateTimeHelpWidget.h"
#include "DateTimeConfigWidget.h"
#include "ui_DateTimeConfigWidget.h"

DateTimeConfigWidget::DateTimeConfigWidget(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::DateTimeConfigWidget),
   m_formatHelpWidget(new DateTimeHelpWidget)
{
   ui->setupUi(this);
   initLocaleComboBox();
}

DateTimeConfigWidget::~DateTimeConfigWidget()
{
   delete ui;
}

void DateTimeConfigWidget::on_formatHelpButton_clicked()
{
   m_formatHelpWidget->show();
}

void DateTimeConfigWidget::initLocaleComboBox()
{
   QString currentLocaleName = QLocale::languageToString(QLocale().language());
   QList<QLocale> allLocales = QLocale::matchingLocales(QLocale::AnyLanguage,
                                                        QLocale::AnyScript,
                                                        QLocale::AnyCountry);

   QMap<QString, QLocale> localeMap;

   for (const QLocale &locale : allLocales) {
       localeMap.insert(QLocale::languageToString(locale.language()), locale);
   }

   QMapIterator<QString, QLocale> it(localeMap);
   while (it.hasNext()) {
      it.next();
      ui->localeCmboBox->addItem(it.key(), QVariant(it.value()));
   }

   ui->localeCmboBox->setCurrentText(currentLocaleName);
}

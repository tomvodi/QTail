/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDebug>
#include <QDateTime>

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
   on_testStringLineEdit_textChanged();
}

DateTimeConfigWidget::~DateTimeConfigWidget()
{
   delete ui;
}

void DateTimeConfigWidget::on_formatHelpButton_clicked()
{
   m_formatHelpWidget->show();
}

void DateTimeConfigWidget::on_testStringLineEdit_textChanged()
{
   checkforEnabledTestButton();
}

void DateTimeConfigWidget::on_formatLineEdit_textChanged()
{
   checkforEnabledTestButton();
}

void DateTimeConfigWidget::on_testButton_clicked()
{
   QLocale selectedLocale = ui->localeCmboBox->currentData().toLocale();

   QDateTime currentDateTime = QDateTime::currentDateTime();
   ui->currentTimestampLabel->setText(selectedLocale.toString(currentDateTime,
                                                              ui->formatLineEdit->text()));

   QDateTime parsedDateTime = selectedLocale.toDateTime(ui->testStringLineEdit->text(),
                                                        ui->formatLineEdit->text());

   bool couldParse = parsedDateTime.isValid();
   if (couldParse) {
      ui->testResultLabel->setPixmap(QPixmap("://resources/icons/emblems/emblem-default.png"));
   } else {
      ui->testResultLabel->setPixmap(QPixmap("://resources/icons/emblems/emblem-dropbox-unsyncable.png"));
   }
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

void DateTimeConfigWidget::checkforEnabledTestButton()
{
   bool buttonEnabled = true;
   if (ui->formatLineEdit->text().isEmpty() ||
       ui->testStringLineEdit->text().isEmpty()) {
      buttonEnabled = false;
   }

   ui->testButton->setEnabled(buttonEnabled);
}

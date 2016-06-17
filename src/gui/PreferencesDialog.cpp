/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDebug>

#include "PreferencesDialog.h"
#include "ui_PreferencesDialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::PreferencesDialog),
   m_settings(new Settings)
{
   ui->setupUi(this);
   initUpdateIntervalComboBox();

   ui->textViewFontPicker->setFontFilters(QFontComboBox::MonospacedFonts);

   Settings settings;

   ui->textViewFontPicker->setCurrentFont(settings.textViewFont());

   connect(ui->textViewFontPicker, &FontPicker::currentFontChanged,
           [this] (const QFont &font){
      m_settings->setTextViewFont(font);
      emit settingsHaveChanged(Settings::TextViewSettings);
   });

   connect(ui->lineWrapCheckBox, &QCheckBox::toggled,
           [this] (bool checked) {
      m_settings->setTextViewLineWrap(checked);
      emit settingsHaveChanged(Settings::TextViewSettings);
   });
   connect(ui->updateIntervalComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
           [this] {
      int currentMilliseconds = ui->updateIntervalComboBox->currentData().toInt();
      if (currentMilliseconds == 0) {
         return;
      }

      m_settings->setTextViewUpdateIntervalMs(currentMilliseconds);
      emit settingsHaveChanged(Settings::TextViewSettings);
   });
}

PreferencesDialog::~PreferencesDialog()
{
   delete ui;
}

ApplicationSettings PreferencesDialog::settings() const
{
    return m_settings;
}

void PreferencesDialog::setSettings(const ApplicationSettings &settings)
{
   m_settings = settings;

   blockSignals(true);

   ui->textViewFontPicker->setCurrentFont(settings->textViewFont());
   ui->lineWrapCheckBox->setChecked(settings->textViewLineWrap());

   blockSignals(false);
}

void PreferencesDialog::initUpdateIntervalComboBox()
{
   QString millisecondsTemplate(tr("%1 milliseconds"));
   QString secondsTemplate(tr("%1 seconds"));
   QString minutesTemplate(tr("%1 minutes"));

   // 10 ms
   int milliseconds = 10;
   ui->updateIntervalComboBox->addItem(millisecondsTemplate.arg(milliseconds), milliseconds);

   // 50 ms
   milliseconds = 50;
   ui->updateIntervalComboBox->addItem(millisecondsTemplate.arg(milliseconds), milliseconds);

   // 100 ms
   milliseconds = 100;
   ui->updateIntervalComboBox->addItem(millisecondsTemplate.arg(milliseconds), milliseconds);

   // 250 ms
   milliseconds = 250;
   ui->updateIntervalComboBox->addItem(millisecondsTemplate.arg(milliseconds), milliseconds);

   // 500 ms
   milliseconds = 500;
   ui->updateIntervalComboBox->addItem(millisecondsTemplate.arg(milliseconds), milliseconds);

   // 1 sec
   int seconds = 1;
   ui->updateIntervalComboBox->addItem(secondsTemplate.arg(seconds), seconds * 1000);

   // 2 sec
   seconds = 2;
   ui->updateIntervalComboBox->addItem(secondsTemplate.arg(seconds), seconds * 1000);

   // 5 sec
   seconds = 5;
   ui->updateIntervalComboBox->addItem(secondsTemplate.arg(seconds), seconds * 1000);

   // 10 sec
   seconds = 10;
   ui->updateIntervalComboBox->addItem(secondsTemplate.arg(seconds), seconds * 1000);

   // 20 sec
   seconds = 20;
   ui->updateIntervalComboBox->addItem(secondsTemplate.arg(seconds), seconds * 1000);

   // 30 sec
   seconds = 30;
   ui->updateIntervalComboBox->addItem(secondsTemplate.arg(seconds), seconds * 1000);

   // 1 min
   int minutes = 1;
   ui->updateIntervalComboBox->addItem(minutesTemplate.arg(minutes), minutes * 60 * 1000);

   // 5 min
   minutes = 5;
   ui->updateIntervalComboBox->addItem(minutesTemplate.arg(minutes), minutes * 60 * 1000);

   // 10 min
   minutes = 10;
   ui->updateIntervalComboBox->addItem(minutesTemplate.arg(minutes), minutes * 60 * 1000);
}

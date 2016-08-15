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

   connect(this, &PreferencesDialog::accepted,
           this, &PreferencesDialog::dialogAccepted);
   connect(this, &PreferencesDialog::rejected,
           this, &PreferencesDialog::dialogRejected);

//   connect(ui->textViewFontPicker, &FontPicker::currentFontChanged,
//           [this] (const QFont &font){
//      m_settings->setTextViewFont(font);
//      emit settingsHaveChanged(Settings::TextViewSettings);
//   });

//   connect(ui->lineWrapCheckBox, &QCheckBox::toggled,
//           [this] (bool checked) {
//      m_settings->setTextViewLineWrap(checked);
//      emit settingsHaveChanged(Settings::TextViewSettings);
//   });
//   connect(ui->updateIntervalComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
//           [this] {
//      int currentMilliseconds = ui->updateIntervalComboBox->currentData().toInt();
//      if (currentMilliseconds == 0) {
//         return;
//      }

//      m_settings->setTextViewUpdateIntervalMs(currentMilliseconds);
//      emit settingsHaveChanged(Settings::TextViewSettings);
//   });
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

   int intervalIndex = ui->updateIntervalComboBox->findData(settings->textViewUpdateIntervalMs());
   if (intervalIndex == -1) {
      intervalIndex = 0;
   }
   ui->updateIntervalComboBox->setCurrentIndex(intervalIndex);

   blockSignals(false);
}

void PreferencesDialog::setAvailableTranslations(const QStringList &languages)
{
   foreach (const QString &language, languages) {
      QLocale locale(language);
      QString languageName = QLocale::languageToString(locale.language());
      ui->languageComboBox->addItem(languageName, language);
   }
}

void PreferencesDialog::setSelectedTranslation(const QString &language)
{
   int languageIndex = ui->languageComboBox->findData(language);
   if (languageIndex != -1) {
      ui->languageComboBox->setCurrentIndex(languageIndex);
   }
}

void PreferencesDialog::dialogAccepted()
{
   if (textViewSettingsHaveBeenModified()) {
      writeTextViewSettings();
      emit settingsHaveChanged(Settings::TextViewSettings);
   }
}

void PreferencesDialog::dialogRejected()
{
   setSettings(m_settings);
}

void PreferencesDialog::changeEvent(QEvent *event)
{
   if (event->type() == QEvent::LanguageChange) {
      ui->retranslateUi(this);
   }

   QDialog::changeEvent(event);
}

void PreferencesDialog::on_buttonBox_clicked(QAbstractButton *button)
{
   if (ui->buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole) {
      dialogAccepted();
   }
}

void PreferencesDialog::on_languageComboBox_currentIndexChanged(int index)
{
   QString newLanguage = ui->languageComboBox->itemData(index).toString();
   emit selectedLanguageChanged(newLanguage);
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

/*!
 * \brief PreferencesDialog::textViewSettingsHaveBeenModified
 * Check if the textview settings in the ui have been changed in comparison to the stored settings.
 * \return
 */
bool PreferencesDialog::textViewSettingsHaveBeenModified() const
{
   if (ui->textViewFontPicker->currentFont() != m_settings->textViewFont()) {
      return true;
   }
   if (ui->lineWrapCheckBox->isChecked() != m_settings->textViewLineWrap()) {
      return true;
   }
   if (ui->updateIntervalComboBox->currentData().toInt() != m_settings->textViewUpdateIntervalMs()) {
      return true;
   }

   return false;
}

void PreferencesDialog::writeTextViewSettings()
{
   m_settings->setTextViewFont(ui->textViewFontPicker->currentFont());
   m_settings->setTextViewLineWrap(ui->lineWrapCheckBox->isChecked());
   m_settings->setTextViewUpdateIntervalMs(ui->updateIntervalComboBox->currentData().toInt());
}

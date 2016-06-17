/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "PreferencesDialog.h"
#include "ui_PreferencesDialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::PreferencesDialog),
   m_settings(new Settings)
{
   ui->setupUi(this);

   ui->textViewFontPicker->setFontFilters(QFontComboBox::MonospacedFonts);

   Settings settings;

   ui->textViewFontPicker->setCurrentFont(settings.textViewFont());

   connect(ui->textViewFontPicker, &FontPicker::currentFontChanged,
           [this] (const QFont &font){
      m_settings->setTextViewFont(font);
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
}

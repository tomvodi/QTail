/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "tools/Settings.h"

#include "PreferencesDialog.h"
#include "ui_PreferencesDialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::PreferencesDialog)
{
   ui->setupUi(this);
   ui->textViewFontPicker->setFontFilters(QFontComboBox::MonospacedFonts);

   Settings settings;

   ui->textViewFontPicker->setCurrentFont(settings.textViewFont());
}

PreferencesDialog::~PreferencesDialog()
{
   delete ui;
}

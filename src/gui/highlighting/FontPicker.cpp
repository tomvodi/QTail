/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "FontPicker.h"
#include "ui_FontPicker.h"

FontPicker::FontPicker(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::FontPicker)
{
   ui->setupUi(this);

   // Init to default font size
   QFont font;
   ui->fontSizeSpinBox->setValue(font.pointSize());
}

FontPicker::~FontPicker()
{
   delete ui;
}

QFont FontPicker::currentFont() const
{
   QFont font(ui->fontComboBox->currentFont());
   if (ui->boldButton->isChecked()) {
      font.setBold(true);
   }
   if (ui->italicButton->isChecked()) {
      font.setItalic(true);
   }
   if (ui->underlineButton->isChecked()) {
      font.setUnderline(true);
   }
   if (ui->strikeoutButton->isChecked()) {
      font.setStrikeOut(true);
   }
   font.setPointSize(ui->fontSizeSpinBox->value());
   return font;
}

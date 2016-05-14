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
}

FontPicker::~FontPicker()
{
   delete ui;
}

QFont FontPicker::currentFont() const
{
   ui->fontComboBox->currentFont();
}

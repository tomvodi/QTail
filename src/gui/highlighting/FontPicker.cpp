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

   createConnections();
}

void FontPicker::createConnections()
{
   connect(ui->fontComboBox, &QFontComboBox::currentFontChanged,
           [this] { emit currentFontChanged(currentFont()); });
   connect(ui->boldButton, &QToolButton::toggled,
           [this] { emit currentFontChanged(currentFont()); });
   connect(ui->italicButton, &QToolButton::toggled,
           [this] { emit currentFontChanged(currentFont()); });
   connect(ui->underlineButton, &QToolButton::toggled,
           [this] { emit currentFontChanged(currentFont()); });
   connect(ui->strikeoutButton, &QToolButton::toggled,
           [this] { emit currentFontChanged(currentFont()); });
   connect(ui->fontSizeSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
           [this] { emit currentFontChanged(currentFont()); });
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

void FontPicker::setCurrentFont(const QFont &font)
{
   ui->fontComboBox->setCurrentFont(font);
   ui->fontSizeSpinBox->setValue(font.pointSize());
   ui->boldButton->setChecked(font.bold());
   ui->italicButton->setChecked(font.italic());
   ui->underlineButton->setChecked(font.underline());
   ui->strikeoutButton->setChecked(font.strikeOut());

   emit currentFontChanged(currentFont());
}

QFontComboBox::FontFilters FontPicker::fontFilters() const
{
   return ui->fontComboBox->fontFilters();
}

void FontPicker::setFontFilters(QFontComboBox::FontFilters fontFilters)
{
   ui->fontComboBox->setFontFilters(fontFilters);
}

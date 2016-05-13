/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDebug>
#include <QColor>
#include <QStringList>

#include "ColorPickerListItemWidget.h"
#include "ColorPicker.h"
#include "ui_ColorPicker.h"

ColorPicker::ColorPicker(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::ColorPicker)
{
   ui->setupUi(this);

   initWithPredefinedColors();
}

ColorPicker::~ColorPicker()
{
   delete ui;
}

void ColorPicker::initWithPredefinedColors()
{
   QStringList predefinedColors = QColor::colorNames();
   qDebug() << predefinedColors;

   foreach (const QString &color, QColor::colorNames()) {
      ColorPickerListItemWidget *itemWidget = new ColorPickerListItemWidget;
      itemWidget->setColor(color);
      QListWidgetItem *item = new QListWidgetItem(ui->colorListWidget);
      item->setSizeHint(itemWidget->sizeHint());

      ui->colorListWidget->addItem(item);
      ui->colorListWidget->setItemWidget(item, itemWidget);
   }
}

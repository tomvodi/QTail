/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "ColorPickerListItemWidget.h"
#include "ui_ColorPickerListItemWidget.h"

ColorPickerListItemWidget::ColorPickerListItemWidget(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::ColorPickerListItemWidget)
{
   ui->setupUi(this);
}

ColorPickerListItemWidget::~ColorPickerListItemWidget()
{
   delete ui;
}

QColor ColorPickerListItemWidget::color() const
{
   return m_color;
}

void ColorPickerListItemWidget::setColor(const QString &colorName)
{
   m_color.setNamedColor(colorName);

   ui->colorFrame->setStyleSheet(QString("background-color: %1").arg(colorName));
   ui->colorNameLabel->setText(colorName);
}

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
#include <QPainter>

#include "ColorPicker.h"
#include "ui_ColorPicker.h"

static const QSize ColorIconSize(30, 50);

ColorPicker::ColorPicker(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::ColorPicker)
{
   ui->setupUi(this);

   initWithPredefinedColors();
   connect(ui->colorComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
           [this] {
      emit currentColorChanged(currentColor());
   });
}

ColorPicker::~ColorPicker()
{
   delete ui;
}

QColor ColorPicker::currentColor() const
{
   QString currentColorName = ui->colorComboBox->currentData().toString();
   QColor color;
   color.setNamedColor(currentColorName);

   return color;
}

void ColorPicker::setCurrentColor(const QColor &color)
{
   QString colorName = color.name();
   int colorIndex = ui->colorComboBox->findData(QColor(colorName));
   if (colorIndex == -1) {
      qWarning() << "Failed to find color " << colorName << " in color combobox.";
   } else {
      ui->colorComboBox->setCurrentIndex(colorIndex);
   }
}

void ColorPicker::initWithPredefinedColors()
{
   QStringList predefinedColors = QColor::colorNames();
   predefinedColors.removeDuplicates();

   QStringList baseColors(baseColorList());
   QStringList moreRedColors;
   QStringList moreGreenColors;
   QStringList moreBlueColors;
   QStringList contrasts;

   foreach (const QString &colorName, QColor::colorNames()) {
      QColor color;
      color.setNamedColor(colorName);

      if (baseColors.contains(colorName)) {
         continue;
      }

      if (color.saturation() == 0) {
         contrasts << colorName;
         continue;
      }

      if (color.red() >= color.blue() &&
          color.red() >= color.green()) {
         moreRedColors << colorName;
         continue;
      }

      if (color.green() >= color.red() &&
          color.green() >= color.blue()) {
         moreGreenColors << colorName;
         continue;
      }

      if (color.blue() >= color.red() &&
          color.blue() >= color.green()) {
         moreBlueColors << colorName;
      }
   }

   foreach (const QString &colorName, colorNamesSortedByLightness(moreBlueColors)) {
      insertColor(colorName);
   }

   ui->colorComboBox->insertSeparator(0);

   foreach (const QString &colorName, colorNamesSortedByLightness(moreGreenColors)) {
      insertColor(colorName);
   }

   ui->colorComboBox->insertSeparator(0);

   foreach (const QString &colorName, colorNamesSortedByLightness(moreRedColors)) {
      insertColor(colorName);
   }

   ui->colorComboBox->insertSeparator(0);

   foreach (const QString &colorName, colorNamesSortedByLightness(contrasts)) {
      insertColor(colorName);
   }

   ui->colorComboBox->insertSeparator(0);

   foreach (const QString &colorName, colorNamesSortedByLightness(baseColors)) {
      if (colorName == "transparent") {
         continue;
      }

      insertColor(colorName);
   }
}

QIcon ColorPicker::iconForColor(const QColor &color)
{
   QPixmap pixmap(ColorIconSize);
   pixmap.fill(color);

   return QIcon(pixmap);
}

QStringList ColorPicker::colorNamesSortedByLightness(const QStringList &colorNames)
{
   QMultiMap<int, QString> sortedColors;

   foreach (const QString &colorName, colorNames) {
      QColor color;
      color.setNamedColor(colorName);
      sortedColors.insert(color.lightness(), colorName);
   }

   QStringList sortedColorNames(sortedColors.values());
   QStringList reverseLightnessColors;

   QList<QString>::const_iterator it(sortedColorNames.constEnd());

   while (it != sortedColorNames.constBegin()) {
      --it;
      reverseLightnessColors << (*it);
   }

   if (colorNames.count() != reverseLightnessColors.count()) {
      qDebug() << "Not all colors are in list";
   }
   return reverseLightnessColors;
}

QStringList ColorPicker::baseColorList() const
{
   // As defined in Qt::GlobalColors
   QStringList globalColors{ "black", "white", "darkGray", "gray", "lightGray", "red",
                             "green", "blue", "cyan", "magenta", "yellow", "darkRed",
                             "darkGreen", "darkBlue", "darkCyan", "darkMagenta", "darkYellow",
                             "transparent" };

   QStringList baseColors;
   foreach (const QString &colorName, globalColors) {
      if (QColor::isValidColor(colorName)) {
         baseColors << colorName;
      }
   }

   return baseColors;
}

void ColorPicker::insertColor(const QString &colorName)
{
   ui->colorComboBox->insertItem(0, iconForColor(colorName), colorName, colorName);
}

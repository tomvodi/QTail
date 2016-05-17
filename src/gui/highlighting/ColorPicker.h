/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QFrame>
#include <QIcon>

namespace Ui {
class ColorPicker;
}

class ColorPicker : public QFrame
{
   Q_OBJECT
   friend class ColorPickerTest;

public:
   explicit ColorPicker(QWidget *parent = 0);
   ~ColorPicker();

   QColor currentColor() const;
   void setCurrentColor(const QColor &color);

signals:
   void currentColorChanged(const QColor &color);

private:
   void initWithPredefinedColors();
   QIcon iconForColor(const QColor &color);
   QStringList colorNamesSortedByLightness(const QStringList &colorNames);
   QStringList baseColorList() const;
   void insertColor(const QString &colorName);
   Ui::ColorPicker *ui;
};

#endif // COLORPICKER_H

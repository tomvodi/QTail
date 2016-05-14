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

public:
   explicit ColorPicker(QWidget *parent = 0);
   ~ColorPicker();

private:
   void initWithPredefinedColors();
   QIcon iconForColor(const QColor &color);
   QStringList colorNamesSortedByLightness(const QStringList &colorNames);
   QStringList baseColorList() const;
   Ui::ColorPicker *ui;
};

#endif // COLORPICKER_H

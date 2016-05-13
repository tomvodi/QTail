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
   Ui::ColorPicker *ui;
};

#endif // COLORPICKER_H

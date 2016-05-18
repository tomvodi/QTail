/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FONTPICKER_H
#define FONTPICKER_H

#include <QFrame>

namespace Ui {
class FontPicker;
}

class FontPicker : public QFrame
{
   Q_OBJECT
   friend class FontPickerTest;

public:
   explicit FontPicker(QWidget *parent = 0);
   ~FontPicker();

   QFont currentFont() const;
   void setCurrentFont(const QFont &font);

signals:
   void currentFontChanged(const QFont &font);

private:
   void createConnections();
   Ui::FontPicker *ui;
};

#endif // FONTPICKER_H

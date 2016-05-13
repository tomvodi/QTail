/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLORPICKERLISTITEMWIDGET_H
#define COLORPICKERLISTITEMWIDGET_H

#include <QFrame>

namespace Ui {
class ColorPickerListItemWidget;
}

class ColorPickerListItemWidget : public QFrame
{
   Q_OBJECT

public:
   explicit ColorPickerListItemWidget(QWidget *parent = 0);
   ~ColorPickerListItemWidget();

   QColor color() const;
   void setColor(const QString &colorName);

private:
   Ui::ColorPickerListItemWidget *ui;
   QColor m_color;
};

#endif // COLORPICKERLISTITEMWIDGET_H

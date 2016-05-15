/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "HighlightListItemDelegate.h"

#include <QPainter>

HighlightListItemDelegate::HighlightListItemDelegate(QObject *parent)
   : QStyledItemDelegate(parent)
{
}

void HighlightListItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{
   if (option.state & QStyle::State_Selected) {
      // get the color to paint with
      QColor backgroundColor = index.model()->data(index, Qt::BackgroundRole).value<QColor>();
      QColor foregroundColor = index.model()->data(index, Qt::ForegroundRole).value<QColor>();
      QFont font = index.model()->data(index, Qt::FontRole).value<QFont>();

      painter->setPen(foregroundColor);
      painter->setFont(font);

      painter->fillRect(option.rect, backgroundColor);
      QRect textRect(option.rect);
      textRect.adjust(3, 0, 0, 0);
      painter->drawText(textRect, index.model()->data(index, Qt::DisplayRole).toString());

      // Draw selection rect
      painter->save();
      QPen pen(Qt::DashDotDotLine);
      pen.setWidth(1);
      pen.setColor(Qt::black);

      QRect selectionRect(option.rect);
      selectionRect.adjust(1, 1, -1, -1);

      painter->setRenderHint(QPainter::Antialiasing);
      painter->setPen(pen);
      painter->drawRoundedRect(selectionRect, 2, 2);

      painter->restore();
   } else {
      QStyledItemDelegate::paint(painter, option, index);
   }
}

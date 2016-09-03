/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDebug>
#include <QPainter>

#include "ColumnGlobals.h"
#include "ColumnDefinitionInterface.h"
#include "ColumnDefinitionDelegate.h"

ColumnDefinitionDelegate::ColumnDefinitionDelegate(QObject *parent)
   : QStyledItemDelegate(parent)
{
}

void ColumnDefinitionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
   if (option.state & QStyle::State_Selected) {
      painter->fillRect(option.rect, option.palette.color(QPalette::Highlight));
   }

   ColumnDefinition definition = index.data(ColumnDefinitionDataRole).value<ColumnDefinition>();
   if (!definition) {
      qWarning() << "Can't use ColumnDefinition in delegate. Data not set";
      return;
   }

   QRect nameRect = option.rect;
   painter->drawText(nameRect, Qt::AlignLeft, definition->name());
}

QSize ColumnDefinitionDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   QSize size(200, 50);

   ColumnDefinition definition = index.data(ColumnDefinitionDataRole).value<ColumnDefinition>();
   if (!definition) {
      qWarning() << "Can't use ColumnDefinition in delegate. Data not set";
      return size;
   }

   QFontMetrics metrics(option.font);
   int height = 2 * metrics.boundingRect("9").height();
   size.setHeight(height);
   size.setWidth(200);

   return size;
}

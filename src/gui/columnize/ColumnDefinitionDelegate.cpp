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

static qreal PaddingLeftRight(0.6); // Item padding left and right
static qreal PaddingTopBottom(0.4); // Item padding top and bottom
static qreal Spacing(0.25);          // Spacing between text lines

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

   QFontMetrics metrics(option.font);

   QRectF nameRect = option.rect;
   QRect charBoundingRect = metrics.boundingRect("9");
   qreal paddingLR = PaddingLeftRight * charBoundingRect.width();
   qreal paddingTopBot = PaddingTopBottom * charBoundingRect.height();
   nameRect.adjust(paddingLR, paddingTopBot, -paddingLR, 0);
   painter->save();
   QFont nameFont(option.font);
   nameFont.setBold(true);
   painter->setFont(nameFont);
   painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignTop, definition->name());
   painter->restore();

   nameRect.adjust(0, charBoundingRect.height() + Spacing * charBoundingRect.height(), 0, 0);

   QFont descriptionFont(option.font);
   descriptionFont.setItalic(true);
   painter->save();
   painter->setFont(descriptionFont);
   painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignTop, definition->description());
   painter->restore();
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
   QRect boundingRectChar = metrics.boundingRect("9");
   int height = 2 * boundingRectChar.height() +
                Spacing * boundingRectChar.height() +
                2 * PaddingTopBottom * boundingRectChar.height();
   size.setHeight(height);

   int maxWidth = qMax(metrics.boundingRect(definition->description()).width(),
                       metrics.boundingRect(definition->name()).width());
   maxWidth += 2 * PaddingLeftRight * boundingRectChar.width();
   size.setWidth(maxWidth);

   return size;
}

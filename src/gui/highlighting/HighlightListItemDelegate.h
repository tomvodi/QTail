/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef HIGHLIGHTLISTITEMDELEGATE_H
#define HIGHLIGHTLISTITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class HighlightListItemDelegate : public QStyledItemDelegate
{
public:
   HighlightListItemDelegate(QObject *parent=0);

   void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // HIGHLIGHTLISTITEMDELEGATE_H

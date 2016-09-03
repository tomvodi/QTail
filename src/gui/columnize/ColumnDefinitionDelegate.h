/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNDEFINITIONDELEGATE_H
#define COLUMNDEFINITIONDELEGATE_H

#include <QStyledItemDelegate>

class ColumnDefinitionDelegate : public QStyledItemDelegate
{
public:
   ColumnDefinitionDelegate(QObject *parent=0);

   // QAbstractItemDelegate interface
public:
   void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
   QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // COLUMNDEFINITIONDELEGATE_H

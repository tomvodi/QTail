/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNGLOBALS_H
#define COLUMNGLOBALS_H

#include <QMetaType>

enum ColumnType {
   Text,   // Arbitrary text
   DateTime,  // A datetime timestamp
   Selection   // A selection of values
};
Q_DECLARE_METATYPE(ColumnType)

static const int ColumnTypeDataRole       = Qt::UserRole + 1;
static const int ColumnDefinitionDataRole = Qt::UserRole + 2;

#endif // COLUMNGLOBALS_H

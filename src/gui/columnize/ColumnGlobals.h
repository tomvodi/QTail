/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNGLOBALS_H
#define COLUMNGLOBALS_H

#include <Qt>

enum ColumnType {
   Text,   // Arbitrary text
   DateTime,  // A datetime timestamp
   Selection   // A selection of values
};

static const int ColumnDefinitionDataRole = Qt::UserRole + 1;

#endif // COLUMNGLOBALS_H

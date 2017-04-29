/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNIZE_GLOBALS_H
#define COLUMNIZE_GLOBALS_H

#include <QMetaType>

enum class ColumnType {
   None,   // No type set
   Text,   // Arbitrary text
   DateTime,  // A datetime timestamp
   Selection   // A selection of values
};
Q_DECLARE_METATYPE(ColumnType)

#endif // COLUMNIZE_GLOBALS_H

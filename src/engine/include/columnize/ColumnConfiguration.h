/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNCONFIGURATION_H
#define COLUMNCONFIGURATION_H

#include <QSharedDataPointer>
#include "columnize_globals.h"

class ColumnConfigurationData;

class ColumnConfiguration
{
public:
   ColumnConfiguration();
   ColumnConfiguration(const ColumnConfiguration &);
   ColumnConfiguration &operator=(const ColumnConfiguration &);
   ~ColumnConfiguration();

   ColumnType type() const;
   void setType(const ColumnType &type);

private:
   QSharedDataPointer<ColumnConfigurationData> data;
};

#endif // COLUMNCONFIGURATION_H

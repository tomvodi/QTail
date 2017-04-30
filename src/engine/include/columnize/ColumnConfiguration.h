/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNCONFIGURATION_H
#define COLUMNCONFIGURATION_H

#include <QJsonObject>
#include <QSharedPointer>

#include <QSharedDataPointer>
#include "columnize_globals.h"

class ColumnConfigurationData;

class ColumnConfiguration
{
public:
   ColumnConfiguration();
   ColumnConfiguration(ColumnType type);
   ColumnConfiguration(const ColumnConfiguration &);
   ColumnConfiguration &operator=(const ColumnConfiguration &);
   ~ColumnConfiguration();

   ColumnType type() const;
   void setType(const ColumnType &type);

   QJsonObject configuration() const;
   void setConfiguration(const QJsonObject &configuration);

private:
   QSharedDataPointer<ColumnConfigurationData> data;
};

using ColConfig = QSharedPointer<ColumnConfiguration>;

#endif // COLUMNCONFIGURATION_H

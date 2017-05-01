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

/*!
 * \brief The ColumnConfiguration class
 * A generic class that holds the configuration of a specific column type.
 * Helper objects of type ColumnConfigurationHelper are meant to read values from objects of this
 * class.
 */
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
   void insert(const QString &key, const QJsonValue &value);
   QJsonValue value(const QString &key) const;

private:
   QSharedDataPointer<ColumnConfigurationData> data;
};

using ColConfig = QSharedPointer<ColumnConfiguration>;

#endif // COLUMNCONFIGURATION_H

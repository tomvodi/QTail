/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNCONFIGURATIONHELPER_H
#define COLUMNCONFIGURATIONHELPER_H

#include <QSharedDataPointer>
#include "ColumnConfiguration.h"

class ColumnConfigurationHelperData;

class ColumnConfigurationHelper
{
   friend class ColumnConfigurationHelperTest;
public:
   ColumnConfigurationHelper(const ColConfig &config);
   ColumnConfigurationHelper(const ColumnConfigurationHelper &);
   ColumnConfigurationHelper &operator=(const ColumnConfigurationHelper &);
   ~ColumnConfigurationHelper();

   ColConfig columnConfiguration() const;

   ColumnType type() const;
   void setType(ColumnType type);

protected:
   void insert(const QString &key, const QJsonValue &value);
   QJsonValue value(const QString &key) const;

private:
   QSharedDataPointer<ColumnConfigurationHelperData> data;
};

#endif // COLUMNCONFIGURATIONHELPER_H

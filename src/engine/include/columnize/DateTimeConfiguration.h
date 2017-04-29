/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef DATETIMECONFIGURATION_H
#define DATETIMECONFIGURATION_H

#include <QSharedDataPointer>
#include "ColumnConfiguration.h"

class DateTimeConfigurationData;

class DateTimeConfiguration : public ColumnConfiguration
{
public:
   DateTimeConfiguration();
   DateTimeConfiguration(const DateTimeConfiguration &);
   DateTimeConfiguration &operator=(const DateTimeConfiguration &);
   ~DateTimeConfiguration();

private:
   QSharedDataPointer<DateTimeConfigurationData> data;
};

#endif // DATETIMECONFIGURATION_H

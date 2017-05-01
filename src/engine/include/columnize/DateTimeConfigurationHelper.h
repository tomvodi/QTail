/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef DATETIMECONFIGURATIONHELPER_H
#define DATETIMECONFIGURATIONHELPER_H

#include "ColumnConfigurationHelper.h"

class DateTimeConfigurationHelper : public ColumnConfigurationHelper
{
public:
   DateTimeConfigurationHelper(const ColConfig &config);

   void setLocale(const QLocale &locale);
   QLocale locale() const;

   QString format() const;
   void setFormat(const QString &format);
};

#endif // DATETIMECONFIGURATIONHELPER_H

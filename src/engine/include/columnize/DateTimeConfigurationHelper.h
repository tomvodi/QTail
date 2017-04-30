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
};

#endif // DATETIMECONFIGURATIONHELPER_H

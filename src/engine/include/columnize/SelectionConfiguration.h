/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef SELECTIONCONFIGURATION_H
#define SELECTIONCONFIGURATION_H

#include <QSharedDataPointer>
#include "ColumnConfiguration.h"

class SelectionConfigurationData;

class SelectionConfiguration : public ColumnConfiguration
{
public:
   SelectionConfiguration();
   SelectionConfiguration(const SelectionConfiguration &);
   SelectionConfiguration &operator=(const SelectionConfiguration &);
   ~SelectionConfiguration();

private:
   QSharedDataPointer<SelectionConfigurationData> data;
};

#endif // SELECTIONCONFIGURATION_H

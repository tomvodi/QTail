/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef SELECTIONCONFIGURATIONHELPER_H
#define SELECTIONCONFIGURATIONHELPER_H

#include "ColumnConfigurationHelper.h"

class SelectionConfigurationHelper : public ColumnConfigurationHelper
{
public:
   SelectionConfigurationHelper(const ColConfig &config);
};

#endif // SELECTIONCONFIGURATIONHELPER_H

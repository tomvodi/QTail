/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef TEXTCONFIGURATIONHELPER_H
#define TEXTCONFIGURATIONHELPER_H

#include "ColumnConfigurationHelper.h"

class TextConfigurationHelper : public ColumnConfigurationHelper
{
public:
   TextConfigurationHelper(const ColConfig &config);
};

#endif // TEXTCONFIGURATIONHELPER_H

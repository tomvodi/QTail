/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef TEXTCONFIGURATION_H
#define TEXTCONFIGURATION_H

#include <QSharedDataPointer>
#include "ColumnConfiguration.h"

class TextConfigurationData;

class TextConfiguration : public ColumnConfiguration
{
public:
   TextConfiguration();
   TextConfiguration(const TextConfiguration &);
   TextConfiguration &operator=(const TextConfiguration &);
   ~TextConfiguration();

private:
   QSharedDataPointer<TextConfigurationData> data;
};

#endif // TEXTCONFIGURATION_H

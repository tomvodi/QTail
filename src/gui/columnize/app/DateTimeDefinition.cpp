/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "DateTimeDefinition.h"

DateTimeDefinition::DateTimeDefinition()
{
}

QString DateTimeDefinition::name() const
{
   return QObject::tr("Timestamp");
}

QString DateTimeDefinition::description() const
{
   return QObject::tr("A column with a timestamp in a configurable format.");
}

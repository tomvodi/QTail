/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QObject>

#include "SelectionDefinition.h"

SelectionDefinition::SelectionDefinition()
{
}

QString SelectionDefinition::name() const
{
   return QObject::tr("Selection");
}

QString SelectionDefinition::description() const
{
   return QObject::tr("A selection of all values in the column.");
}

/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QObject>

#include "TextDefinition.h"

TextDefinition::TextDefinition()
{
}

QString TextDefinition::name() const
{
   return QObject::tr("Text");
}

QString TextDefinition::description() const
{
   return QObject::tr("A column with arbitrary text.");
}

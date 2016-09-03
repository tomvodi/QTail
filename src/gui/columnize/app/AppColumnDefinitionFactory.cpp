/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "DateTimeDefinition.h"
#include "SelectionDefinition.h"
#include "TextDefinition.h"
#include "AppColumnDefinitionFactory.h"

AppColumnDefinitionFactory::AppColumnDefinitionFactory()
{
}

QList<ColumnType> AppColumnDefinitionFactory::supportedTypes() const
{
    return QList<ColumnType>() << ColumnType::Text << ColumnType::DateTime << ColumnType::Selection;
}

ColumnDefinition AppColumnDefinitionFactory::getDefinition(ColumnType type)
{
   switch (type) {
   case Text:
      return ColumnDefinition(new TextDefinition);
      break;
   case DateTime:
      return ColumnDefinition(new DateTimeDefinition);
      break;
   case Selection:
      return ColumnDefinition(new SelectionDefinition);
      break;
   }

   return ColumnDefinition(nullptr);
}

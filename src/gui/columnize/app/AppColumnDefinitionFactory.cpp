/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "datetime/DateTimeDefinition.h"
#include "selection/SelectionDefinition.h"
#include "text/TextDefinition.h"
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
   ColumnDefinition definition;
   switch (type) {
   case ColumnType::Text:
      definition = ColumnDefinition(new TextDefinition);
      break;
   case ColumnType::DateTime:
      definition = ColumnDefinition(new DateTimeDefinition);
      break;
   case ColumnType::Selection:
      definition = ColumnDefinition(new SelectionDefinition);
      break;
   case ColumnType::None:
      break;
   }

   if (definition) {
      definition->setType(type);
   }

   return definition;
}

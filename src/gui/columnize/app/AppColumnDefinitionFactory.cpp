/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "AppColumnDefinitionFactory.h"

AppColumnDefinitionFactory::AppColumnDefinitionFactory()
{
}

QList<ColumnType> AppColumnDefinitionFactory::supportedTypes() const
{
    return QList<ColumnType>();
}

ColumnDefinition AppColumnDefinitionFactory::getDefinition(ColumnType type)
{
    return ColumnDefinition();
}

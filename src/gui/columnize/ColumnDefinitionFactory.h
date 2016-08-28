/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNDEFINITIONFACTORY_H
#define COLUMNDEFINITIONFACTORY_H

#include <QSharedPointer>

#include "ColumnDefinitionInterface.h"
#include "ColumnGlobals.h"

class ColumnDefinitionFactory
{
public:
   ColumnDefinitionFactory();
   virtual ~ColumnDefinitionFactory();

   virtual QList<ColumnType> supportedTypes() const = 0;
   virtual ColumnDefinition getDefinition(ColumnType type) = 0;
};

typedef QSharedPointer<ColumnDefinitionFactory> ColumnFactory;

#endif // COLUMNDEFINITIONFACTORY_H

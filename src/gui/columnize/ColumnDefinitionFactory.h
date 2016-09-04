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

   /*!
    * \brief supportedTypes
    * Get a list of all supported definition types of this factory.
    */
   virtual QList<ColumnType> supportedTypes() const = 0;
   /*!
    * \brief getDefinition
    * Returns a newly created definition.
    */
   virtual ColumnDefinition getDefinition(ColumnType type) = 0;
};

typedef QSharedPointer<ColumnDefinitionFactory> ColumnFactory;

#endif // COLUMNDEFINITIONFACTORY_H

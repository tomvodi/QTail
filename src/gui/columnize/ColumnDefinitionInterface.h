/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef COLUMNDEFINITIONINTERFACE_H
#define COLUMNDEFINITIONINTERFACE_H

#include <QSharedPointer>

class ColumnDefinitionInterface
{
public:
   ColumnDefinitionInterface();
   virtual ~ColumnDefinitionInterface();
};

typedef QSharedPointer<ColumnDefinitionInterface> ColumnDefinition;

#endif // COLUMNDEFINITIONINTERFACE_H

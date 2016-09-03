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

   virtual QString name() const = 0;
   virtual QString description() const = 0;
};

typedef QSharedPointer<ColumnDefinitionInterface> ColumnDefinition;

Q_DECLARE_METATYPE(ColumnDefinition)

#endif // COLUMNDEFINITIONINTERFACE_H

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

#include "ColumnGlobals.h"

class ColumnDefinitionInterface
{
public:
   ColumnDefinitionInterface();
   virtual ~ColumnDefinitionInterface();

   virtual QString name() const = 0;
   virtual QString description() const = 0;

   ColumnType type() const;
   void setType(const ColumnType &type);

private:
   ColumnType m_type;
};

typedef QSharedPointer<ColumnDefinitionInterface> ColumnDefinition;

Q_DECLARE_METATYPE(ColumnDefinition)

#endif // COLUMNDEFINITIONINTERFACE_H

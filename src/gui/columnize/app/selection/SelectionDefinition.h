/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef SELECTIONDEFINITION_H
#define SELECTIONDEFINITION_H

#include <ColumnDefinitionInterface.h>

class SelectionDefinition : public ColumnDefinitionInterface
{
public:
   SelectionDefinition();

   // ColumnDefinitionInterface interface
public:
   QString name() const override;
   QString description() const override;
};

#endif // SELECTIONDEFINITION_H

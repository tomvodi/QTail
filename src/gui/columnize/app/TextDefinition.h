/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef TEXTDEFINITION_H
#define TEXTDEFINITION_H

#include "../ColumnDefinitionInterface.h"

class TextDefinition : public ColumnDefinitionInterface
{
public:
   TextDefinition();

   // ColumnDefinitionInterface interface
public:
   QString name() const override;
   QString description() const override;
};

#endif // TEXTDEFINITION_H

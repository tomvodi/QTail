/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef DATETIMEDEFINITION_H
#define DATETIMEDEFINITION_H

#include "../ColumnDefinitionInterface.h"

class DateTimeDefinition : public ColumnDefinitionInterface
{
public:
   DateTimeDefinition();

   // ColumnDefinitionInterface interface
public:
   QString name() const override;
   QString description() const override;
};

#endif // DATETIMEDEFINITION_H

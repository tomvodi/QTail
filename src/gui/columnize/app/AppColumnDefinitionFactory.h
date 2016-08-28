/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef APPCOLUMNDEFINITIONFACTORY_H
#define APPCOLUMNDEFINITIONFACTORY_H

#include "../ColumnDefinitionFactory.h"

/*!
 * \brief The AppColumnDefinitionFactory class
 * This is the concrete column definition factory for the application
 */
class AppColumnDefinitionFactory : public ColumnDefinitionFactory
{
public:
   AppColumnDefinitionFactory();

   // ColumnDefinitionFactory interface
public:
   QList<ColumnType> supportedTypes() const override;
   ColumnDefinition getDefinition(ColumnType type) override;
};

#endif // APPCOLUMNDEFINITIONFACTORY_H

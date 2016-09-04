/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "ColumnDefinitionInterface.h"

ColumnDefinitionInterface::ColumnDefinitionInterface()
{
}

ColumnDefinitionInterface::~ColumnDefinitionInterface()
{
}

/*!
 * \brief ColumnDefinitionInterface::configWidget
 * Subclasses can return a widget that configures this specific definition. E.g. the format
 * of the datetime column.
 * \return
 */
QWidget *ColumnDefinitionInterface::configWidget() const
{
   return nullptr;
}

ColumnType ColumnDefinitionInterface::type() const
{
    return m_type;
}

void ColumnDefinitionInterface::setType(const ColumnType &type)
{
    m_type = type;
}

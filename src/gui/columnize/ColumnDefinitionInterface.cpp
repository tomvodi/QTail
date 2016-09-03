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

ColumnType ColumnDefinitionInterface::type() const
{
    return m_type;
}

void ColumnDefinitionInterface::setType(const ColumnType &type)
{
    m_type = type;
}

/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/columnize/ColumnConfiguration.h"

class ColumnConfigurationData : public QSharedData
{
public:
   ColumnType type = ColumnType::None;
};

ColumnConfiguration::ColumnConfiguration()
   : data(new ColumnConfigurationData)
{

}

ColumnConfiguration::ColumnConfiguration(const ColumnConfiguration &rhs)
   : data(rhs.data)
{

}

ColumnConfiguration &ColumnConfiguration::operator=(const ColumnConfiguration &rhs)
{
   if (this != &rhs)
      data.operator=(rhs.data);
   return *this;
}

ColumnConfiguration::~ColumnConfiguration()
{

}

ColumnType ColumnConfiguration::type() const
{
   return data->type;
}

void ColumnConfiguration::setType(const ColumnType &type)
{
   data->type = type;
}

/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/columnize/ColumnConfigurationHelper.h"

class ColumnConfigurationHelperData : public QSharedData
{
public:
   ColConfig colConfig;
};

ColumnConfigurationHelper::ColumnConfigurationHelper(const ColConfig &config)
   : data(new ColumnConfigurationHelperData)
{
   data->colConfig = config;
}

ColumnConfigurationHelper::ColumnConfigurationHelper(const ColumnConfigurationHelper &rhs)
   : data(rhs.data)
{

}

ColumnConfigurationHelper &ColumnConfigurationHelper::operator=(const ColumnConfigurationHelper &rhs)
{
   if (this != &rhs)
      data.operator=(rhs.data);
   return *this;
}

ColumnConfigurationHelper::~ColumnConfigurationHelper()
{

}

ColConfig ColumnConfigurationHelper::columnConfiguration() const
{
   return data->colConfig;
}

ColumnType ColumnConfigurationHelper::type() const
{
   return data->colConfig->type();
}

void ColumnConfigurationHelper::setType(ColumnType type)
{
   data->colConfig->setType(type);
}

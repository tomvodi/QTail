/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "ColumnConfigurationHelper.h"

class ColumnConfigurationHelperData : public QSharedData
{
public:

};

ColumnConfigurationHelper::ColumnConfigurationHelper() : data(new ColumnConfigurationHelperData)
{

}

ColumnConfigurationHelper::ColumnConfigurationHelper(const ColumnConfigurationHelper &rhs) : data(rhs.data)
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

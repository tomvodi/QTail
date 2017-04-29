/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/columnize/SelectionConfiguration.h"

class SelectionConfigurationData : public QSharedData
{
public:

};

SelectionConfiguration::SelectionConfiguration()
    : data(new SelectionConfigurationData)
{
   setType(ColumnType::Selection);
}

SelectionConfiguration::SelectionConfiguration(const SelectionConfiguration &rhs)
    : data(rhs.data)
{

}

SelectionConfiguration &SelectionConfiguration::operator=(const SelectionConfiguration &rhs)
{
   if (this != &rhs)
      data.operator=(rhs.data);
   return *this;
}

SelectionConfiguration::~SelectionConfiguration()
{

}

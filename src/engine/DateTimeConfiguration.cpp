/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/columnize/DateTimeConfiguration.h"

class DateTimeConfigurationData : public QSharedData
{
public:

};

DateTimeConfiguration::DateTimeConfiguration()
    : data(new DateTimeConfigurationData)
{
   setType(ColumnType::DateTime);
}

DateTimeConfiguration::DateTimeConfiguration(const DateTimeConfiguration &rhs)
    : data(rhs.data)
{

}

DateTimeConfiguration &DateTimeConfiguration::operator=(const DateTimeConfiguration &rhs)
{
   if (this != &rhs)
      data.operator=(rhs.data);
   return *this;
}

DateTimeConfiguration::~DateTimeConfiguration()
{

}

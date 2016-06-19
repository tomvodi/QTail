/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/FilterGroup.h"

class FilterGroupData : public QSharedData
{
public:
   QString name;
};

FilterGroup::FilterGroup()
   : data(new FilterGroupData)
{
}

FilterGroup::FilterGroup(const QString &name)
   : data(new FilterGroupData)
{
   setName(name);
}

FilterGroup::FilterGroup(const FilterGroup &rhs)
   : data(rhs.data)
{
}

FilterGroup &FilterGroup::operator=(const FilterGroup &rhs)
{
   if (this != &rhs)
      data.operator=(rhs.data);
   return *this;
}

FilterGroup::~FilterGroup()
{
}

QString FilterGroup::name() const
{
   return data->name;
}

void FilterGroup::setName(const QString &name)
{
   data->name = name;
}

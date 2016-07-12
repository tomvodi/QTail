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
   QList<FilterRule> rules;
};

FilterGroup::FilterGroup()
   : data(new FilterGroupData)
{
   qRegisterMetaType<FilterGroup>("FilterGroup");
}

FilterGroup::FilterGroup(const QString &name)
   : data(new FilterGroupData)
{
   qRegisterMetaType<FilterGroup>("FilterGroup");
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

bool FilterGroup::operator==(const FilterGroup &other) const
{
   if (name() != other.name()) {
      return false;
   }

//   if (filterRules() != other.filterRules()) {
//      return false;
//   }

   return true;
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

QList<FilterRule> FilterGroup::filterRules() const
{
   return data->rules;
}

void FilterGroup::setFilterRules(const QList<FilterRule> &rules)
{
   data->rules = rules;
}

void FilterGroup::addFilterRule(const FilterRule &rule)
{
   data->rules.append(rule);
}

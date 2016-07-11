/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/FilterRule.h"

class FilterRuleData : public QSharedData
{
public:
   QString filter;
   Qt::CaseSensitivity caseSensitivity = Qt::CaseInsensitive;
   bool active = true;
};

FilterRule::FilterRule() : data(new FilterRuleData)
{

}

FilterRule::FilterRule(const QString &regEx)
   : data(new FilterRuleData)
{
   setFilter(regEx);
}

FilterRule::FilterRule(const FilterRule &rhs) : data(rhs.data)
{

}

FilterRule &FilterRule::operator=(const FilterRule &rhs)
{
   if (this != &rhs)
      data.operator=(rhs.data);
   return *this;
}

bool FilterRule::operator==(const FilterRule &other) const
{
   if (data->caseSensitivity != other.caseSensitivity()) {
      return false;
   }

   if (data->filter != other.filter()) {
      return false;
   }

   if (data->active != other.active()) {
      return false;
   }

   return true;
}

FilterRule::~FilterRule()
{
}

QString FilterRule::filter() const
{
   return data->filter;
}

void FilterRule::setFilter(const QString &regEx)
{
   data->filter = regEx;
}

Qt::CaseSensitivity FilterRule::caseSensitivity() const
{
   return data->caseSensitivity;
}

void FilterRule::setCaseSensitivity(const Qt::CaseSensitivity &caseSensitivity)
{
   data->caseSensitivity = caseSensitivity;
}

bool FilterRule::active() const
{
   return data->active;
}

void FilterRule::setActive(bool active)
{
   data->active = active;
}

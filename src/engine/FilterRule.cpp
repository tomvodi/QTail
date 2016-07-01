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

bool FilterRule::operator==(const FilterRule &other)
{
   if (this->data == other.data) {
      return true;
   }

   return false;
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

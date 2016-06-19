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

};

FilterRule::FilterRule() : data(new FilterRuleData)
{

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

FilterRule::~FilterRule()
{

}

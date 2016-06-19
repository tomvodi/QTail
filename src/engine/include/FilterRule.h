/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILTERRULE_H
#define FILTERRULE_H

#include <QSharedDataPointer>

class FilterRuleData;

class FilterRule
{
public:
   FilterRule();
   FilterRule(const FilterRule &);
   FilterRule &operator=(const FilterRule &);
   ~FilterRule();

private:
   QSharedDataPointer<FilterRuleData> data;
};

#endif // FILTERRULE_H
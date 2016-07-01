/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILTERRULE_H
#define FILTERRULE_H

#include <QString>
#include <QSharedDataPointer>

class FilterRuleData;

class FilterRule
{
public:
   FilterRule();
   FilterRule(const QString &regEx);
   FilterRule(const FilterRule &);
   FilterRule &operator=(const FilterRule &);
   bool operator==(const FilterRule &other);
   ~FilterRule();

   QString filter() const;
   void setFilter(const QString &regEx);

   Qt::CaseSensitivity caseSensitivity() const;
   void setCaseSensitivity(const Qt::CaseSensitivity &caseSensitivity);

private:
   QSharedDataPointer<FilterRuleData> data;
};

#endif // FILTERRULE_H

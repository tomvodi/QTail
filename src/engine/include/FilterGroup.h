/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILTERGROUP_H
#define FILTERGROUP_H

#include <QList>
#include <QMetaType>
#include <QSharedDataPointer>

#include "FilterRule.h"

class FilterGroupData;

class FilterGroup
{
public:
   FilterGroup();
   FilterGroup(const QString &name);
   FilterGroup(const FilterGroup &);
   FilterGroup &operator=(const FilterGroup &);
   ~FilterGroup();

   QString name() const;
   void setName(const QString &name);

   QList<FilterRule> filterRules() const;
   void setFilterRules(const QList<FilterRule> &rules);
   void addFilterRule(const FilterRule &rule);

private:
   QSharedDataPointer<FilterGroupData> data;
};

Q_DECLARE_METATYPE(FilterGroup)

#endif // FILTERGROUP_H

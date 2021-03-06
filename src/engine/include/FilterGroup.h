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
#include <QJsonObject>
#include <QSharedDataPointer>
#include <QUuid>

#include "FilterRule.h"

class FilterGroupData;

class FilterGroup
{
public:
   FilterGroup();
   FilterGroup(const QString &name);
   FilterGroup(const FilterGroup &);
   FilterGroup &operator=(const FilterGroup &);
   bool operator==(const FilterGroup &other) const;
   ~FilterGroup();

   QUuid id() const;
   void setid(const QUuid &id);

   QString name() const;
   void setName(const QString &name);

   QList<FilterRule> filterRules() const;
   void setFilterRules(const QList<FilterRule> &rules);
   void addFilterRule(const FilterRule &rule);

   QJsonObject toJson() const;
   void fromJson(const QJsonObject &json);

   static QList<FilterRule> activeRulesForIds(const QList<FilterGroup> &groups, const QList<QUuid> &activeFilterIds);

private:
   QSharedDataPointer<FilterGroupData> data;
};

Q_DECLARE_METATYPE(FilterGroup)

#endif // FILTERGROUP_H

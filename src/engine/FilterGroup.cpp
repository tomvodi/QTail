/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/FilterGroup.h"

#include <QJsonArray>

const QString NameValueName("name");
const QString RulesValueName("rules");

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

   if (filterRules() != other.filterRules()) {
      return false;
   }

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

QJsonObject FilterGroup::toJson() const
{
   QJsonObject json;
   json.insert(NameValueName, data->name);

   QJsonArray filterArray;
   foreach (const FilterRule &rule, data->rules) {
      filterArray.append(rule.toJson());
   }
   json.insert(RulesValueName, filterArray);

   return json;
}

void FilterGroup::fromJson(const QJsonObject &json)
{
   data->name = json.value(NameValueName).toString();

   data->rules.clear();
   QJsonArray filterArray = json.value(RulesValueName).toArray();
   foreach (const QJsonValue &value, filterArray) {
      QJsonObject json = value.toObject();
      if (json.isEmpty()) {
         continue;
      }

      FilterRule rule;
      rule.fromJson(json);

      data->rules.append(rule);
   }
}

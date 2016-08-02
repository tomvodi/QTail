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
#include <QJsonObject>
#include <QSharedDataPointer>
#include <QUuid>
#include <QMetaType>

class FilterRuleData;

class FilterRule
{
public:
   FilterRule();
   FilterRule(const QString &regEx);
   FilterRule(const FilterRule &);
   FilterRule &operator=(const FilterRule &);
   bool operator==(const FilterRule &other) const;
   ~FilterRule();

   QUuid id() const;
   void setId(const QUuid &id);

   QString filter() const;
   void setFilter(const QString &regEx);

   Qt::CaseSensitivity caseSensitivity() const;
   void setCaseSensitivity(const Qt::CaseSensitivity &caseSensitivity);

   bool isActive() const;
   void setActive(bool isActive);

   QJsonObject toJson() const;
   void fromJson(const QJsonObject &json);

private:
   QSharedDataPointer<FilterRuleData> data;
};

Q_DECLARE_METATYPE(FilterRule)

#endif // FILTERRULE_H

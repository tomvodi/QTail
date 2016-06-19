/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILTERGROUP_H
#define FILTERGROUP_H

#include <QSharedDataPointer>

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

private:
   QSharedDataPointer<FilterGroupData> data;
};

#endif // FILTERGROUP_H

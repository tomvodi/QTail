/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "OpenFileSettings.h"

OpenFileSettings::OpenFileSettings()
{
   qRegisterMetaTypeStreamOperators<OpenFileSettings>("OpenFileSettings");
}

QList<QUuid> OpenFileSettings::activeFilterIds() const
{
    return m_activeFilterIds;
}

void OpenFileSettings::setActiveFilterIds(const QList<QUuid> &filterRuleIds)
{
   m_activeFilterIds = filterRuleIds;
}

bool OpenFileSettings::operator==(const OpenFileSettings &other) const
{
   if (other.activeFilterIds() != activeFilterIds()) {
      return false;
   }

   return true;
}

QDataStream &operator<<(QDataStream &out, const OpenFileSettings &settings)
{
   out << settings.activeFilterIds();
   return out;
}

QDataStream &operator>>(QDataStream &in, OpenFileSettings &settings)
{
   QList<QUuid> activeFilterIds;
   in >> activeFilterIds;
   settings.setActiveFilterIds(activeFilterIds);

   return in;
}

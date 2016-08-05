/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QList>
#include <QUuid>
#include <QMetaType>
#include <QDataStream>

#ifndef OPENFILESETTINGS_H
#define OPENFILESETTINGS_H

/*!
 * \brief The OpenFileSettings class
 * Represents the settings of an opened file.
 */
class OpenFileSettings
{
public:
   OpenFileSettings();

   QList<QUuid> activeFilterIds() const;
   void setActiveFilterIds(const QList<QUuid> &activeFilterIds);

   bool operator==(const OpenFileSettings &other) const;

private:
   QList<QUuid> m_activeFilterIds;
};

Q_DECLARE_METATYPE(OpenFileSettings)

QDataStream& operator<<(QDataStream& out, const OpenFileSettings& settings);
QDataStream& operator>>(QDataStream& in, OpenFileSettings& settings);

#endif // OPENFILESETTINGS_H

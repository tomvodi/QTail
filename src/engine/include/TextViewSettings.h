/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef TEXTVIEWSETTINGS_H
#define TEXTVIEWSETTINGS_H

#include <QFont>
#include <QSharedDataPointer>

class TextViewSettingsData;

class TextViewSettings
{
public:
   TextViewSettings();
   TextViewSettings(const TextViewSettings &);
   TextViewSettings &operator=(const TextViewSettings &);
   bool operator==(const TextViewSettings &other);
   bool operator!=(const TextViewSettings &other);
   ~TextViewSettings();

   QFont font() const;
   void setFont(const QFont &value);

   bool lineWrapOn() const;
   void setLineWrapOn(bool on);

   quint32 updateInterval() const;
   void setUpdateInterval(const quint32 &value);

private:
   QSharedDataPointer<TextViewSettingsData> data;
};

#endif // TEXTVIEWSETTINGS_H

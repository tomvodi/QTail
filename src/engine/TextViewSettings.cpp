/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/TextViewSettings.h"

class TextViewSettingsData : public QSharedData
{
public:
   QFont font;
   bool lineWrap = true;
   quint32 updateInterval = 250;
};

TextViewSettings::TextViewSettings()
   : data(new TextViewSettingsData)
{
}

TextViewSettings::TextViewSettings(const TextViewSettings &rhs)
   : data(rhs.data)
{
}

TextViewSettings &TextViewSettings::operator=(const TextViewSettings &rhs)
{
   if (this != &rhs)
      data.operator=(rhs.data);
   return *this;
}

bool TextViewSettings::operator==(const TextViewSettings &other)
{
   return (data == other.data);
}

bool TextViewSettings::operator!=(const TextViewSettings &other)
{
   return !((*this) == other);
}

TextViewSettings::~TextViewSettings()
{
}

QFont TextViewSettings::font() const
{
   return data->font;
}

void TextViewSettings::setFont(const QFont &value)
{
   data->font = value;
}

bool TextViewSettings::lineWrapOn() const
{
   return data->lineWrap;
}

void TextViewSettings::setLineWrapOn(bool on)
{
   data->lineWrap = on;
}

quint32 TextViewSettings::updateInterval() const
{
   return data->updateInterval;
}

void TextViewSettings::setUpdateInterval(const quint32 &value)
{
   data->updateInterval = value;
}

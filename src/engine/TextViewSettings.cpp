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

bool TextViewSettings::lineWrap() const
{
   return data->lineWrap;
}

void TextViewSettings::setLineWrap(bool value)
{
   data->lineWrap = value;
}

quint32 TextViewSettings::updateInterval() const
{
   return data->updateInterval;
}

void TextViewSettings::setUpdateInterval(const quint32 &value)
{
   data->updateInterval = value;
}

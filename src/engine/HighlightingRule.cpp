/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QColor>
#include <QFont>

#include "include/HighlightingRule.h"

class HighlightingRuleData : public QSharedData
{
public:
   HighlightingRuleData() {}
   ~HighlightingRuleData() {}

   QColor foregroundColor = QColor(Qt::black);
   QColor backgroundColor = QColor(Qt::white);
   QFont  font;
   QString text;
   Qt::CaseSensitivity caseSensitivity = Qt::CaseSensitive;
};

HighlightingRule::HighlightingRule()
   : data(new HighlightingRuleData)
{
}

HighlightingRule::HighlightingRule(const HighlightingRule &rhs)
   : data(rhs.data)
{

}

HighlightingRule &HighlightingRule::operator=(const HighlightingRule &rhs)
{
   if (this != &rhs)
      data.operator=(rhs.data);
   return *this;
}

bool HighlightingRule::operator==(const HighlightingRule &other)
{
   if (data->foregroundColor != other.foregroundColor()) {
      return false;
   }
   if (data->backgroundColor != other.backgroundColor()) {
      return false;
   }
   if (data->font != other.font()) {
      return false;
   }
   if (data->text != other.text()) {
      return false;
   }
   if (data->caseSensitivity != other.caseSensitivity()) {
      return false;
   }

   return true;
}

HighlightingRule::~HighlightingRule()
{
}

QFont HighlightingRule::font() const
{
   return data->font;
}

void HighlightingRule::setFont(const QFont &font)
{
   data->font = font;
}

QColor HighlightingRule::foregroundColor() const
{
   return data->foregroundColor;
}

void HighlightingRule::setForegroundColor(const QColor &foregroundColor)
{
   data->foregroundColor = foregroundColor;
}

QColor HighlightingRule::backgroundColor() const
{
   return data->backgroundColor;
}

void HighlightingRule::setBackgroundColor(const QColor &backgroundColor)
{
   data->backgroundColor = backgroundColor;
}

QString HighlightingRule::text() const
{
   return data->text;
}

void HighlightingRule::setText(const QString &text)
{
   data->text = text;
}

Qt::CaseSensitivity HighlightingRule::caseSensitivity() const
{
   return data->caseSensitivity;
}

void HighlightingRule::setCaseSensitivity(const Qt::CaseSensitivity &caseSensitivity)
{
   data->caseSensitivity = caseSensitivity;
}

QDebug operator<<(QDebug debug, const HighlightingRule &c)
{
   QDebugStateSaver saver(debug);
   QString caseSensitive(c.caseSensitivity() == Qt::CaseSensitive ? "true" : "false");
   debug.nospace() << "HighlightingRule(" << c.text() <<
                      ", bg-color: " << c.backgroundColor() <<
                      ", fg-color: " << c.foregroundColor() <<
                      ", font: " << c.font() <<
                      ", casesensitive: " << caseSensitive <<
                      ')';

   return debug;
}

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
   HighlightingRuleData(const HighlightingRuleData &other) {}

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

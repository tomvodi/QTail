/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef HIGHLIGHTINGRULE_H
#define HIGHLIGHTINGRULE_H

#include <QColor>
#include <QFont>
#include <QSharedDataPointer>

class HighlightingRuleData;

class HighlightingRule
{
public:
   HighlightingRule();
   HighlightingRule(const HighlightingRule &);
   HighlightingRule &operator=(const HighlightingRule &);
   ~HighlightingRule();

   QFont font() const;
   void setFont(const QFont &font);

   QColor foregroundColor() const;
   void setForegroundColor(const QColor &foregroundColor);

   QColor backgroundColor() const;
   void setBackgroundColor(const QColor &backgroundColor);

   QString text() const;
   void setText(const QString &text);

   Qt::CaseSensitivity caseSensitivity() const;
   void setCaseSensitivity(const Qt::CaseSensitivity &caseSensitivity);

private:
   QSharedDataPointer<HighlightingRuleData> data;
};

#endif // HIGHLIGHTINGRULE_H

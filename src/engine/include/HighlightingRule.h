/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef HIGHLIGHTINGRULE_H
#define HIGHLIGHTINGRULE_H

#include <QDebug>
#include <QColor>
#include <QFont>
#include <QMetaType>
#include <QSharedDataPointer>
#include <QJsonObject>
#include <QDataStream>

class HighlightingRuleData;

class HighlightingRule
{
public:
   HighlightingRule();
   HighlightingRule(const HighlightingRule &);
   HighlightingRule &operator=(const HighlightingRule &);
   bool operator==(const HighlightingRule &other) const;
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

   QJsonObject toJson() const;
   void fromJson(const QJsonObject &json);

private:
   QSharedDataPointer<HighlightingRuleData> data;
};

Q_DECLARE_METATYPE(HighlightingRule)

QDebug operator<<(QDebug debug, const HighlightingRule &c);

QDataStream &operator<<(QDataStream &out, const HighlightingRule &rule);
QDataStream &operator>>(QDataStream &in, HighlightingRule &rule);

#endif // HIGHLIGHTINGRULE_H

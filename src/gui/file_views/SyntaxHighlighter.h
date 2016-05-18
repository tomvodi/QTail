/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>

#include <include/HighlightingRule.h>

class SyntaxHighlighter : public QSyntaxHighlighter
{
public:
   SyntaxHighlighter(QTextDocument *document=0);

public slots:
   void setHighlightingRules(const QList<HighlightingRule> &lineRules,
                             const QList<HighlightingRule> &wordRules);

   // QSyntaxHighlighter interface
protected:
   void highlightBlock(const QString &text) override;

private:
   QList<HighlightingRule> m_lineRules;
   QList<HighlightingRule> m_wordRules;
};

#endif // SYNTAXHIGHLIGHTER_H

/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QRegExp>

#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *document)
   : QSyntaxHighlighter(document)
{
}

void SyntaxHighlighter::setHighlightingRules(const QList<HighlightingRule> &lineRules,
                                             const QList<HighlightingRule> &wordRules)
{
   m_lineRules = lineRules;
   m_wordRules = wordRules;

   rehighlight();
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
   // Highlight lines in descending priority. If a rule matches, no other rules will be checked.
   foreach (const HighlightingRule &rule, m_lineRules) {
      if (rule.text().isEmpty()) {
         continue;
      }

      QRegExp expression(rule.text(), rule.caseSensitivity());
      int index = expression.indexIn(text);
      if (index >= 0) {
         QTextCharFormat format;
         format.setFont(rule.font());
         format.setBackground(rule.backgroundColor());
         format.setForeground(rule.foregroundColor());

         setFormat(0, text.length(), format);
         break;
      }
   }

   // Highlighting words has to be after line highlighting
   // There, all rules will be applied in reverse order, so that the high priority rule
   // matches last
   QList<HighlightingRule>::const_iterator it = m_wordRules.constEnd();
   while (it != m_wordRules.constBegin()) {
      --it;
      const HighlightingRule rule(*it);
      if (rule.text().isEmpty()) {
         continue;
      }

      QRegExp expression(rule.text(), rule.caseSensitivity());
      int index = expression.indexIn(text);
      while (index >= 0) {
         QTextCharFormat format;
         format.setFont(rule.font());
         format.setBackground(rule.backgroundColor());
         format.setForeground(rule.foregroundColor());

         int length = expression.matchedLength();
         setFormat(index, length, format);
         index = expression.indexIn(text, index + length);
      }
   }
}

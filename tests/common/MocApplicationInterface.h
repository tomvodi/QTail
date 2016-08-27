/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef MOCAPPLICATIONINTERFACE_H
#define MOCAPPLICATIONINTERFACE_H

#include <include/ApplicationInterface.h>

class MocApplicationInterface : public ApplicationInterface
{
public:
   MocApplicationInterface();

   // ApplicationInterface interface
public:
   void addWordHighlightingRule(const HighlightingRule &rule) override;
   void addLineHighlightingRule(const HighlightingRule &rule) override;

   QList<HighlightingRule> wordHighlightingRules() const;
   QList<HighlightingRule> lineHighlightingRules() const;

private:
   QList<HighlightingRule> m_wordHighlightingRules;
   QList<HighlightingRule> m_lineHighlightingRules;
};

#endif // MOCAPPLICATIONINTERFACE_H

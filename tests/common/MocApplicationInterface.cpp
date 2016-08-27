/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "MocApplicationInterface.h"

MocApplicationInterface::MocApplicationInterface()
{

}


void MocApplicationInterface::addWordHighlightingRule(const HighlightingRule &rule)
{
}

void MocApplicationInterface::addLineHighlightingRule(const HighlightingRule &rule)
{
}

QList<HighlightingRule> MocApplicationInterface::wordHighlightingRules() const
{
   return m_wordHighlightingRules;
}

QList<HighlightingRule> MocApplicationInterface::lineHighlightingRules() const
{
   return m_lineHighlightingRules;
}

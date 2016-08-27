/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "highlighting/HighlightingDialog.h"

#include "ViewApplication.h"

ViewApplication::ViewApplication()
{
}

void ViewApplication::addWordHighlightingRule(const HighlightingRule &rule)
{
   if (m_highlightingDialog) {
      m_highlightingDialog->addWordHighlightingRule(rule);
      m_highlightingDialog->show();
   }
}

void ViewApplication::addLineHighlightingRule(const HighlightingRule &rule)
{
   if (m_highlightingDialog) {
      m_highlightingDialog->addLineHighlightingRule(rule);
      m_highlightingDialog->show();
   }
}

QPointer<HighlightingDialog> ViewApplication::highlightingDialog() const
{
   return m_highlightingDialog;
}

void ViewApplication::setHighlightingDialog(const QPointer<HighlightingDialog> &highlightingDialog)
{
   m_highlightingDialog = highlightingDialog;
}

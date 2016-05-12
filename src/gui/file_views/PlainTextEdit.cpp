/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "PlainTextEdit.h"

PlainTextEdit::PlainTextEdit(QWidget *parent)
   : QPlainTextEdit(parent)
{
   setCenterOnScroll(true);
   setReadOnly(true);
}

void PlainTextEdit::setScrollEnabled(bool enabled)
{
   m_scrollEnabled = enabled;
}

bool PlainTextEdit::scrollEnabled() const
{
   return m_scrollEnabled;
}

void PlainTextEdit::scrollContentsBy(int dx, int dy)
{
   if (!m_scrollEnabled) {
      return;
   }

   QPlainTextEdit::scrollContentsBy(dx, dy);
}

/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "LineNumberArea.h"
#include "PlainTextEdit.h"

LineNumberArea::LineNumberArea(PlainTextEdit *textEdit)
   : QWidget(textEdit),
     m_textEdit(textEdit)
{
}

QSize LineNumberArea::sizeHint() const
{
   if (!m_textEdit) {
      return QWidget::sizeHint();
   }

   return QSize(m_textEdit->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
   if (!m_textEdit) {
      return;
   }

   m_textEdit->lineNumberAreaPaintEvent(event);
}

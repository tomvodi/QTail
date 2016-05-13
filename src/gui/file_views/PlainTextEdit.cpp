/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QPainter>
#include <QTextBlock>

#include "PlainTextEdit.h"
#include "LineNumberArea.h"

PlainTextEdit::PlainTextEdit(QWidget *parent)
   : QPlainTextEdit(parent),
     m_lineNumberArea(new LineNumberArea(this))
{
   setReadOnly(true);

   connect(this, &PlainTextEdit::blockCountChanged,
           this, &PlainTextEdit::updateLineNumberAreaWidth);
   connect(this, &PlainTextEdit::updateRequest,
           this, &PlainTextEdit::updateLineNumberArea);
   connect(this, &PlainTextEdit::cursorPositionChanged,
           this, &PlainTextEdit::highlightCurrentLine);
}

quint16 PlainTextEdit::lineNumberAreaWidth() const
{
   int digits = 1;
   int max = qMax(1, blockCount());
   while (max >= 10) {
      max /= 10;
      ++digits;
   }

   int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

   return space;
}

void PlainTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
   QPainter painter(m_lineNumberArea.data());
   painter.fillRect(event->rect(), Qt::lightGray);
   QTextBlock block = firstVisibleBlock();
   int blockNumber = block.blockNumber();
   int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
   int bottom = top + (int) blockBoundingRect(block).height();

   while (block.isValid() && top <= event->rect().bottom()) {
      if (block.isVisible() && bottom >= event->rect().top()) {
         QString number = QString::number(blockNumber + 1);
         painter.setPen(Qt::black);
         painter.drawText(0, top, m_lineNumberArea->width(), fontMetrics().height(),
                          Qt::AlignRight, number);
      }

      block = block.next();
      top = bottom;
      bottom = top + (int) blockBoundingRect(block).height();
      ++blockNumber;
   }
}

void PlainTextEdit::resizeEvent(QResizeEvent *event)
{
   QPlainTextEdit::resizeEvent(event);

   QRect cr = contentsRect();
   m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(),
                                       lineNumberAreaWidth(), cr.height()));
}

void PlainTextEdit::updateLineNumberAreaWidth(int newBlockCount)
{
   setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void PlainTextEdit::highlightCurrentLine()
{
   QList<QTextEdit::ExtraSelection> extraSelections;

   QTextEdit::ExtraSelection selection;

   QColor lineColor = QColor(Qt::yellow).lighter(160);

   selection.format.setBackground(lineColor);
   selection.format.setProperty(QTextFormat::FullWidthSelection, true);
   selection.cursor = textCursor();
   selection.cursor.clearSelection();
   extraSelections.append(selection);

   setExtraSelections(extraSelections);
}

void PlainTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
   if (dy)
      m_lineNumberArea->scroll(0, dy);
   else
      m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());

   if (rect.contains(viewport()->rect()))
      updateLineNumberAreaWidth(0);
}

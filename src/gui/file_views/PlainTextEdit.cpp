/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QPainter>
#include <QTextBlock>
#include <QScrollBar>
#include <QContextMenuEvent>
#include <QMenu>
#include <QTextDocumentFragment>

#include "PlainTextEdit.h"
#include "LineNumberArea.h"

static const QLatin1Char MetricsBaseChar('9');

// The paddings of the line number in the line number area.
// This number represents the percentage of the width of the MetricsBaseChar
static const qreal LineAreaLeftPadding = 0.7;
static const qreal LineAreaRightPadding = 0.4;

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

   QFontMetrics metrics(m_lineNumberArea->font());
   int charWidth(metrics.width(MetricsBaseChar));
   int leftPadding = lineNumberAreaLeftPadding(metrics);
   int rightPadding = lineNumberAreaRightPadding(metrics);
   int width = leftPadding + rightPadding + charWidth * digits;

   return width;
}

int PlainTextEdit::lineNumberAreaLeftPadding(const QFontMetrics &metrics) const
{
   int charWidth(metrics.width(MetricsBaseChar));
   return qRound(LineAreaLeftPadding * charWidth);
}

int PlainTextEdit::lineNumberAreaRightPadding(const QFontMetrics &metrics) const
{
   int charWidth(metrics.width(MetricsBaseChar));
   return qRound(LineAreaRightPadding * charWidth);
}

void PlainTextEdit::adjustViewportMarginsForLineNumberArea()
{
   setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void PlainTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
   QPainter painter(m_lineNumberArea.data());
   painter.fillRect(event->rect(), Qt::lightGray);
   QTextBlock block = firstVisibleBlock();
   int blockNumber = block.blockNumber();
   int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
   int bottom = top + (int) blockBoundingRect(block).height();

   painter.save();
   QPen pen(Qt::darkGray, 1.0);
   painter.setPen(pen);
   painter.drawLine(event->rect().width() - pen.width(), event->rect().top(),
                    event->rect().width() - pen.width(), event->rect().bottom());
   painter.restore();

   QFontMetrics numberAreaMetrics(m_lineNumberArea->font());
   int rightPadding = lineNumberAreaRightPadding(numberAreaMetrics);
   int numberAreaWidth = lineNumberAreaWidth() - rightPadding;
   int numberAreaLineHeight = numberAreaMetrics.height();

   while (block.isValid() && top <= event->rect().bottom()) {
      if (block.isVisible() && bottom >= event->rect().top()) {
         QString number = QString::number(blockNumber + 1);
         painter.setPen(Qt::black);
         painter.drawText(0, top, numberAreaWidth, numberAreaLineHeight, Qt::AlignRight, number);
      }

      block = block.next();
      top = bottom;
      bottom = top + (int) blockBoundingRect(block).height();
      ++blockNumber;
   }
}

void PlainTextEdit::setLineNumberAreaFont(const QFont &font)
{
   m_lineNumberArea->setFont(font);
   adjustViewportMarginsForLineNumberArea();
}

void PlainTextEdit::scrollToTop()
{
   verticalScrollBar()->setValue(0);
}

void PlainTextEdit::scrollToBottom()
{
   verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

void PlainTextEdit::scrollToCursor()
{
   setCenterOnScroll(true);
   ensureCursorVisible();
   setCenterOnScroll(false);
}

void PlainTextEdit::resizeEvent(QResizeEvent *event)
{
   QPlainTextEdit::resizeEvent(event);

   QRect cr = contentsRect();
   m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(),
                                       lineNumberAreaWidth(), cr.height()));
}

void PlainTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
   QMenu *menu = createStandardContextMenu(event->pos());

   // From here on, add actions that depending on a current text selection.
   QAction *textSelectedAction = nullptr;
   QString selectedText;
   QTextCursor cursor = textCursor();
   if (!cursor.hasSelection()) {
      goto exec_menu;
   }
   selectedText = cursor.selection().toPlainText();

   textSelectedAction = menu->addAction(tr("Create line highlight rule"));
   connect(textSelectedAction, &QAction::triggered, [this, selectedText] {
      HighlightingRule rule(selectedText);
      emit addLineHighlightRequested(rule);
   });

   textSelectedAction = menu->addAction(tr("Create word highlight rule"));
   connect(textSelectedAction, &QAction::triggered, [this, selectedText] {
      HighlightingRule rule(selectedText);
      emit addWordHighlightRequested(rule);
   });

exec_menu:
   menu->exec(event->globalPos());
   delete menu;
}

void PlainTextEdit::updateLineNumberAreaWidth(int newBlockCount)
{
   adjustViewportMarginsForLineNumberArea();
}

void PlainTextEdit::highlightCurrentLine()
{
   QList<QTextEdit::ExtraSelection> extraSelections;

   QTextEdit::ExtraSelection selection;

   QColor lineBackgroundColor = QColor(Qt::yellow).lighter(160);
   QColor lineForegroundColor = QColor(Qt::black);

   selection.format.setBackground(lineBackgroundColor);
   selection.format.setForeground(lineForegroundColor);
   selection.format.setProperty(QTextFormat::FullWidthSelection, true);
   selection.cursor = textCursor();
   selection.cursor.clearSelection();

   extraSelections.append(selection);

   setExtraSelections(extraSelections);
}

void PlainTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
   if (dy) {
      m_lineNumberArea->scroll(0, dy);
   } else {
      m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());
   }

   if (rect.contains(viewport()->rect())) {
      updateLineNumberAreaWidth(0);
   }
}

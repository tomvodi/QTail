/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

#include <QPointer>
#include <QPlainTextEdit>

#include <include/HighlightingRule.h>

class LineNumberArea;

class PlainTextEdit : public QPlainTextEdit
{
   Q_OBJECT
public:
   PlainTextEdit(QWidget *parent=0);

   inline quint16 lineNumberAreaWidth() const;
   void lineNumberAreaPaintEvent(QPaintEvent *event);

   void setLineNumberAreaFont(const QFont &font);

public slots:
   void scrollToTop();
   void scrollToBottom();
   void scrollToCursor();

protected:
   void resizeEvent(QResizeEvent *event) override;
   void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
   void updateLineNumberAreaWidth(int newBlockCount);
   void highlightCurrentLine();
   void updateLineNumberArea(const QRect &rect, int dy);

signals:
   void addLineHighlightRequested(const HighlightingRule &rule);
   void addWordHighlightRequested(const HighlightingRule &rule);

private:
   inline int lineNumberAreaLeftPadding(const QFontMetrics &metrics) const;
   inline int lineNumberAreaRightPadding(const QFontMetrics &metrics) const;
   void adjustViewportMarginsForLineNumberArea();
   QPointer<LineNumberArea> m_lineNumberArea;
   QFont m_lineNumberFont;
};

#endif // PLAINTEXTEDIT_H

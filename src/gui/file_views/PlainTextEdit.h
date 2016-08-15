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

class LineNumberArea;

class PlainTextEdit : public QPlainTextEdit
{
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

private slots:
   void updateLineNumberAreaWidth(int newBlockCount);
   void highlightCurrentLine();
   void updateLineNumberArea(const QRect &rect, int dy);

private:
   inline int lineNumberAreaLeftPadding(const QFontMetrics &metrics) const;
   inline int lineNumberAreaRightPadding(const QFontMetrics &metrics) const;
   void adjustViewportMarginsForLineNumberArea();
   QPointer<LineNumberArea> m_lineNumberArea;
   QFont m_lineNumberFont;
};

#endif // PLAINTEXTEDIT_H

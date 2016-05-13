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

   quint16 lineNumberAreaWidth() const;
   void lineNumberAreaPaintEvent(QPaintEvent *event);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
   QPointer<LineNumberArea> m_lineNumberArea;
};

#endif // PLAINTEXTEDIT_H

/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include <QPointer>

class PlainTextEdit;

class LineNumberArea : public QWidget
{
   Q_OBJECT
public:
   LineNumberArea(PlainTextEdit *textEdit);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
   QPointer<PlainTextEdit> m_textEdit;
};

#endif // LINENUMBERAREA_H

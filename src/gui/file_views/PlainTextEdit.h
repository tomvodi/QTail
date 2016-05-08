/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

#include <QFrame>

namespace Ui {
class PlainTextEdit;
}

class PlainTextEdit : public QFrame
{
   Q_OBJECT
   friend class PlainTextEditTest;

public:
   explicit PlainTextEdit(QWidget *parent = 0);
   ~PlainTextEdit();

   void appendPlainText(const QString &text);
   QString toPlainText() const;
   void clear();

private:
   Ui::PlainTextEdit *ui;
};

#endif // PLAINTEXTEDIT_H

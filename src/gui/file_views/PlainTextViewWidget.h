/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef PLAINTEXTVIEWWIDGET_H
#define PLAINTEXTVIEWWIDGET_H

#include <QFrame>

namespace Ui {
class PlainTextViewWidget;
}

class PlainTextViewWidget : public QFrame
{
   Q_OBJECT

public:
   explicit PlainTextViewWidget(QWidget *parent = 0);
   ~PlainTextViewWidget();

   void appendPlainText(const QString &text);
   QString toPlainText() const;
   void clear();

protected:
   void changeEvent(QEvent *e);

private:
   void setFollowTailEnabled(bool enabled);
   Ui::PlainTextViewWidget *ui;
};

#endif // PLAINTEXTVIEWWIDGET_H

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

   friend class PlainTextViewWidgetTest;
public:
   explicit PlainTextViewWidget(QWidget *parent = 0);
   ~PlainTextViewWidget();

   void appendPlainText(const QString &text);
   QString toPlainText() const;
   void clear();

protected:
   void changeEvent(QEvent *e);

private slots:
   void setFollowTailEnabled(bool enabled);

private:
   Ui::PlainTextViewWidget *ui;
};

#endif // PLAINTEXTVIEWWIDGET_H

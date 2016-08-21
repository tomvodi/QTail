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
class QTextDocument;
class TextViewSettings;

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

   bool lineWrapOn() const;

   void setTextDocument(QTextDocument *document);

   void setTextViewSettings(const TextViewSettings &settings);

protected:
   void changeEvent(QEvent *e);

private slots:
   void searchDocument(const QString &text, Qt::CaseSensitivity caseSensitive);

private:
   void setLineWrapOn(bool lineWrapOn);
   Ui::PlainTextViewWidget *ui;
   void creteConnections();
};

#endif // PLAINTEXTVIEWWIDGET_H

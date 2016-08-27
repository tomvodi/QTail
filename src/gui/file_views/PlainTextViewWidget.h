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
#include <QTextCursor>

#include <include/ApplicationInterface.h>

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

   void setApplicationInterface(const Application &app);
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
   void gotoNextResult();
   void gotoPreviousResult();
   void gotoFirstResult();
   void gotoLastResult();
   void clearSearch();

private:
   void setLineWrapOn(bool lineWrapOn);
   void creteConnections();
   void initActions();
   Ui::PlainTextViewWidget *ui;
   QList<QTextCursor> m_searchResults;
   QTextCursor m_currentSearchResult;
   void jumpToHighlightResult(const QTextCursor &cursor);
};

#endif // PLAINTEXTVIEWWIDGET_H

/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QScrollBar>
#include <QTextDocument>

#include <include/TextViewSettings.h>

#include "PlainTextViewWidget.h"
#include "ui_PlainTextViewWidget.h"

PlainTextViewWidget::PlainTextViewWidget(QWidget *parent) :
   QFrame(parent),
   ui(new Ui::PlainTextViewWidget)
{
   ui->setupUi(this);

   creteConnections();
}

void PlainTextViewWidget::creteConnections()
{
   connect(ui->navigateBottomButton, &QToolButton::clicked,
           ui->plainTextEdit, &PlainTextEdit::scrollToBottom);
   connect(ui->navigateTopButton, &QToolButton::clicked,
           ui->plainTextEdit, &PlainTextEdit::scrollToTop);
   connect(ui->navigateCursorButton, &QToolButton::clicked,
           ui->plainTextEdit, &PlainTextEdit::scrollToCursor);
   connect(ui->searchBar, &SearchBar::searchTriggered,
           this, &PlainTextViewWidget::searchDocument);
}

PlainTextViewWidget::~PlainTextViewWidget()
{
   delete ui;
}

void PlainTextViewWidget::changeEvent(QEvent *e)
{
   QFrame::changeEvent(e);
   switch (e->type()) {
   case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
   default:
      break;
   }
}

void PlainTextViewWidget::searchDocument(const QString &text, Qt::CaseSensitivity caseSensitive)
{
   QList<QTextCursor> allResults;
   QTextCursor firstResult;

   QTextDocument::FindFlags findFlags;
   if (caseSensitive == Qt::CaseSensitive) {
      findFlags |= QTextDocument::FindCaseSensitively;
   }

   QPlainTextEdit *textEdit = ui->plainTextEdit;
   QTextDocument *textDocument = textEdit->document();
   QTextCursor currentCursor = textEdit->textCursor();

   // Find all results forwards beginning from current cursor
   QTextCursor findCursor = textDocument->find(text, currentCursor, findFlags);
   if (!findCursor.isNull()) {
      // Set to first result after current cursor pos
      firstResult = findCursor;
   }

   while (!findCursor.isNull()) {
      allResults.append(findCursor);
      findCursor = textDocument->find(text, findCursor, findFlags);
   }

   // Find all results backwards beginning from current cursor
   findFlags |= QTextDocument::FindBackward;
   findCursor = textDocument->find(text, currentCursor, findFlags);
   while (!findCursor.isNull()) {
      allResults.prepend(findCursor);
      findCursor = textDocument->find(text, findCursor, findFlags);
   }

   if (allResults.isEmpty()) {
      ui->searchBar->setResultNumberAndCount(0, 0);
      return;
   }

   if (firstResult.isNull()) {
      // Set to first result because after current cursor pos wasn't a search match
      firstResult = allResults.at(0);
   }

   ui->searchBar->setResultNumberAndCount(allResults.indexOf(firstResult), allResults.count());

   QTextCharFormat searchResultFormat;
   searchResultFormat.setFont(textDocument->defaultFont());
   searchResultFormat.setBackground(Qt::darkGreen);
   searchResultFormat.setForeground(Qt::yellow);

   QList<QTextEdit::ExtraSelection> searchSelections;
   foreach (const QTextCursor &cursor, allResults) {
      if (cursor.isNull()) {
         continue;
      }
      QTextEdit::ExtraSelection selection;
      selection.format = searchResultFormat;
      selection.cursor = cursor;
      searchSelections.append(selection);
   }

   ui->plainTextEdit->setTextCursor(firstResult);
   ui->plainTextEdit->ensureCursorVisible();
   ui->plainTextEdit->setExtraSelections(searchSelections);
}

bool PlainTextViewWidget::lineWrapOn() const
{
   return (ui->plainTextEdit->lineWrapMode() == QPlainTextEdit::WidgetWidth);
}

void PlainTextViewWidget::setLineWrapOn(bool lineWrapOn)
{
   if (lineWrapOn) {
      ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
   } else {
      ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
   }
}

void PlainTextViewWidget::setTextViewSettings(const TextViewSettings &settings)
{
   ui->plainTextEdit->document()->setDefaultFont(settings.font());
   ui->plainTextEdit->setLineNumberAreaFont(settings.font());
   setLineWrapOn(settings.lineWrapOn());
}

void PlainTextViewWidget::appendPlainText(const QString &text)
{
    ui->plainTextEdit->appendPlainText(text);
}

QString PlainTextViewWidget::toPlainText() const
{
   return ui->plainTextEdit->toPlainText();
}

void PlainTextViewWidget::clear()
{
   ui->plainTextEdit->clear();
}

void PlainTextViewWidget::setTextDocument(QTextDocument *document)
{
   ui->plainTextEdit->setDocument(document);
}

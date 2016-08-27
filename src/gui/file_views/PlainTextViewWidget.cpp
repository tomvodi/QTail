/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDebug>
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

   initActions();
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
   connect(ui->searchBar, &SearchBar::gotoFirstResult,
           this, &PlainTextViewWidget::gotoFirstResult);
   connect(ui->searchBar, &SearchBar::gotoNextResult,
           this, &PlainTextViewWidget::gotoNextResult);
   connect(ui->searchBar, &SearchBar::gotoPreviousResult,
           this, &PlainTextViewWidget::gotoPreviousResult);
   connect(ui->searchBar, &SearchBar::gotoLastResult,
           this, &PlainTextViewWidget::gotoLastResult);
   connect(ui->searchBar, &SearchBar::searchCleared,
           this, &PlainTextViewWidget::clearSearch);
}

void PlainTextViewWidget::initActions()
{
   QKeySequence startSearchShortcut(QKeySequence::Find);
   QAction *startSearchAction = new QAction(this);
   startSearchAction->setShortcut(startSearchShortcut);
   connect(startSearchAction, &QAction::triggered,
           [this] {
      QString selectedText = ui->plainTextEdit->textCursor().selectedText();
      if (selectedText.isEmpty()) {
         return;
      }

      ui->searchBar->startSearch(selectedText);
   });

   addAction(startSearchAction);
}

PlainTextViewWidget::~PlainTextViewWidget()
{
   delete ui;
}

void PlainTextViewWidget::setApplicationInterface(const Application &app)
{
   connect(ui->plainTextEdit, &PlainTextEdit::addLineHighlightRequested,
           [app] (const HighlightingRule &rule) {
      app->addLineHighlightingRule(rule);
   });
   connect(ui->plainTextEdit, &PlainTextEdit::addWordHighlightRequested,
           [app] (const HighlightingRule &rule) {
      app->addWordHighlightingRule(rule);
   });
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
   m_currentSearchResult = QTextCursor();
   m_searchResults.clear();

   QTextDocument::FindFlags findFlags;
   if (caseSensitive == Qt::CaseSensitive) {
      findFlags |= QTextDocument::FindCaseSensitively;
   }

   QPlainTextEdit *textEdit = ui->plainTextEdit;
   QTextDocument *textDocument = textEdit->document();
   QTextCursor currentCursor = textEdit->textCursor();
   currentCursor.clearSelection(); // To get QTextDocument::find to work properly

   // Find all results forwards beginning from current cursor
   QTextCursor findCursor = textDocument->find(text, currentCursor, findFlags);
   if (!findCursor.isNull()) {
      // Set to first result after current cursor pos
      m_currentSearchResult = findCursor;
   }

   while (!findCursor.isNull()) {
      m_searchResults.append(findCursor);
      findCursor = textDocument->find(text, findCursor, findFlags);
   }

   // Find all results backwards beginning from current cursor
   findFlags |= QTextDocument::FindBackward;
   findCursor = textDocument->find(text, currentCursor, findFlags);
   while (!findCursor.isNull()) {
      m_searchResults.prepend(findCursor);
      findCursor = textDocument->find(text, findCursor, findFlags);
   }

   if (m_searchResults.isEmpty()) {
      ui->searchBar->setResultNumberAndCount(0, 0);
      return;
   }

   if (m_currentSearchResult.isNull()) {
      // Set to first result because after current cursor pos wasn't a search match
      m_currentSearchResult = m_searchResults.at(0);
   }

   jumpToHighlightResult(m_currentSearchResult);
}

void PlainTextViewWidget::jumpToHighlightResult(const QTextCursor &cursor)
{
   ui->searchBar->setResultNumberAndCount(m_searchResults.indexOf(cursor) + 1, m_searchResults.count());

   QTextCharFormat searchResultFormat;
   searchResultFormat.setFont(ui->plainTextEdit->document()->defaultFont());
   searchResultFormat.setBackground(Qt::darkGreen);
   searchResultFormat.setForeground(Qt::yellow);

   QList<QTextEdit::ExtraSelection> searchSelections;
   foreach (const QTextCursor &cursor, m_searchResults) {
      if (cursor.isNull()) {
         continue;
      }
      QTextEdit::ExtraSelection selection;
      selection.format = searchResultFormat;
      selection.cursor = cursor;
      searchSelections.append(selection);
   }

   ui->plainTextEdit->setTextCursor(cursor);
   ui->plainTextEdit->ensureCursorVisible();
   ui->plainTextEdit->setExtraSelections(searchSelections);
}

void PlainTextViewWidget::gotoNextResult()
{
   if (m_searchResults.isEmpty() ||
       m_currentSearchResult.isNull()) {
      return;
   }

   int resultIndex = m_searchResults.indexOf(m_currentSearchResult);
   if (resultIndex == -1) {
      return;
   }

   resultIndex++;
   if (resultIndex > (m_searchResults.count() - 1)) {
      resultIndex = 0;
   }

   QTextCursor cursor = m_searchResults.at(resultIndex);
   if (cursor == m_currentSearchResult) {
      return;
   }
   m_currentSearchResult = cursor;

   if (!cursor.isNull()) {
      jumpToHighlightResult(cursor);
   }
}

void PlainTextViewWidget::gotoPreviousResult()
{
   if (m_searchResults.isEmpty() ||
       m_currentSearchResult.isNull()) {
      return;
   }

   int resultIndex = m_searchResults.indexOf(m_currentSearchResult);
   if (resultIndex == -1) {
      return;
   }

   resultIndex--;

   if (resultIndex < 0) {
      resultIndex = m_searchResults.count() - 1;
   }

   QTextCursor cursor = m_searchResults.at(resultIndex);
   if (cursor == m_currentSearchResult) {
      return;
   }
   m_currentSearchResult = cursor;

   if (!cursor.isNull()) {
      jumpToHighlightResult(cursor);
   }
}

void PlainTextViewWidget::gotoFirstResult()
{
   if (m_searchResults.isEmpty()) {
      return;
   }

   QTextCursor cursor = m_searchResults.first();
   if (cursor == m_currentSearchResult) {
      return;
   }
   m_currentSearchResult = cursor;

   if (!cursor.isNull()) {
      jumpToHighlightResult(cursor);
   }
}

void PlainTextViewWidget::gotoLastResult()
{
   if (m_searchResults.isEmpty()) {
      return;
   }

   QTextCursor cursor = m_searchResults.last();
   if (cursor == m_currentSearchResult) {
      return;
   }
   m_currentSearchResult = cursor;

   if (!cursor.isNull()) {
      jumpToHighlightResult(cursor);
   }
}

void PlainTextViewWidget::clearSearch()
{
   m_searchResults.clear();
   m_currentSearchResult = QTextCursor();

   ui->plainTextEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
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

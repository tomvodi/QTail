/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QTextDocument>
#include <QPlainTextDocumentLayout>
#include <QRegularExpression>

#include <include/TextViewSettings.h>

#include "PlainTextViewWidget.h"
#include "PlainTextView.h"
#include "SyntaxHighlighter.h"

PlainTextView::PlainTextView(QObject *parent)
   : FileViewInterface(parent),
     m_textEdit(new PlainTextViewWidget)
{
   m_textDocument = new QTextDocument(this);
   m_textDocument->setDocumentLayout(new QPlainTextDocumentLayout(m_textDocument));

   m_syntaxHighlighter = new SyntaxHighlighter(m_textDocument);
   m_textEdit->setTextDocument(m_textDocument);
}

FileViewInterface::Features PlainTextView::viewFeatures() const
{
   return FileViewInterface::HasTextView;
}

void PlainTextView::appendLine(const QString &line)
{
   if (m_textEdit) {
      m_textEdit->appendPlainText(line);
   }
}

void PlainTextView::appendLines(const QStringList &lines)
{
   if (!m_textEdit) {
      return;
   }

   foreach (const QString &line, lines) {
      appendLine(line);
   }
}

void PlainTextView::clearTextView()
{
   if (m_textEdit) {
      m_textEdit->clear();
   }
}

void PlainTextView::readCompleteFileUntil(qint64 maxLength)
{
   QFile file(fileInfo().absoluteFilePath());
   if (!file.open(QIODevice::ReadOnly)) {
      qWarning() << "readCompleteFileUntil: Failed opening file for reading.";
      return;
   }

   clearTextView();

   // No filters => read all
   if (m_activeFilters.isEmpty()) {
      m_textEdit->appendPlainText(file.read(maxLength));
      return;
   }

   // With filters
   while (!file.atEnd()) {
      QString line(file.readLine());
      if (lineHasToBeFilteredOut(line)) {
         continue;
      }

      m_textEdit->appendPlainText(line.trimmed());
   }
}

bool PlainTextView::lineHasToBeFilteredOut(const QString &line) const
{
   foreach (const FilterRule &filter, m_activeFilters) {
      QRegularExpression regEx(filter.filter());
      if (filter.caseSensitivity() == Qt::CaseInsensitive) {
         regEx.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
      }
      QRegularExpressionMatch match = regEx.match(line);
      if (match.hasMatch()) {
         return true;
      }
   }

   return false;
}

QPointer<QWidget> PlainTextView::widget() const
{
   return QPointer<QWidget>(m_textEdit);
}

void PlainTextView::setHighlightingRules(const QList<HighlightingRule> &lineRules,
                                         const QList<HighlightingRule> &wordRules)
{
   m_syntaxHighlighter->setHighlightingRules(lineRules, wordRules);
}

void PlainTextView::setTextViewSettings(const TextViewSettings &settings)
{
   m_textDocument->setDefaultFont(settings.font());
   m_textEdit->setLineWrapOn(settings.lineWrapOn());
}

void PlainTextView::setActiveFilters(const QList<FilterRule> &filters)
{
   m_activeFilters = filters;
}

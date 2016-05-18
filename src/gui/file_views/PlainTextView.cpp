/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QTextDocument>
#include <QPlainTextDocumentLayout>

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

QPointer<QWidget> PlainTextView::widget() const
{
   return QPointer<QWidget>(m_textEdit);
}

void PlainTextView::setHighlightingRules(const QList<HighlightingRule> &lineRules,
                                         const QList<HighlightingRule> &wordRules)
{
   m_syntaxHighlighter->setHighlightingRules(lineRules, wordRules);
}

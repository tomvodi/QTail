/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "PlainTextEdit.h"
#include "PlainTextView.h"

PlainTextView::PlainTextView()
   : m_textEdit(new PlainTextEdit)
{
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

QPointer<PlainTextEdit> PlainTextView::textEdit() const
{
   return m_textEdit;
}

QPointer<QWidget> PlainTextView::widget() const
{
   return QPointer<QWidget>(m_textEdit);
}

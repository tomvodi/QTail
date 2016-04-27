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

}

void PlainTextView::appendLines(const QStringList &lines)
{
}

void PlainTextView::clearTextView()
{
}

QPointer<PlainTextEdit> PlainTextView::textEdit() const
{
   return m_textEdit;
}

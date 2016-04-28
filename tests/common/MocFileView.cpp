/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "MocFileView.h"

MocFileView::MocFileView()
{
}

FileViewInterface::Features MocFileView::viewFeatures() const
{
   return m_viewFeatures;
}

void MocFileView::setFileState(FileState state)
{
   m_fileState = state;
   m_fileStateWasSetByInterfaceMethod = true;
}

void MocFileView::appendLine(const QString &line)
{
   m_textViewLines.append(line);
}

void MocFileView::appendLines(const QStringList &lines)
{
   m_textViewLines.append(lines);
}

void MocFileView::clearTextView()
{
   m_textViewLines.clear();
}

QStringList MocFileView::textViewLines() const
{
   return m_textViewLines;
}

void MocFileView::setTextViewLines(const QStringList &textViewLines)
{
   m_textViewLines = textViewLines;
}

bool MocFileView::fileStateWasSetByInterfaceMethod() const
{
   return m_fileStateWasSetByInterfaceMethod;
}

FileState MocFileView::fileState() const
{
   return m_fileState;
}

void MocFileView::setViewFeatures(const FileViewInterface::Features &viewFeatures)
{
   m_viewFeatures = viewFeatures;
}

/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "MocFileView.h"

MocFileView::MocFileView(QObject *parent)
   : FileViewInterface(parent)
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

void MocFileView::readCompleteFileUntil(qint64 maxLength)
{
   m_readUntilMaxLength = maxLength;
}

void MocFileView::setFileInfo(const QFileInfo &fileInfo)
{
   m_fileInfo = fileInfo;
}

void MocFileView::setFileActive(bool active)
{
   m_fileActive = active;
}

QStringList MocFileView::textViewLines() const
{
   return m_textViewLines;
}

void MocFileView::setTextViewLines(const QStringList &textViewLines)
{
   m_textViewLines = textViewLines;
}

TextViewSettings MocFileView::textViewSettings() const
{
   return m_textViewSettings;
}

void MocFileView::setTextViewSettings(const TextViewSettings &textViewSettings)
{
   m_textViewSettings = textViewSettings;
}

bool MocFileView::fileActive() const
{
   return m_fileActive;
}

qint64 MocFileView::readUntilMaxLength() const
{
   return m_readUntilMaxLength;
}

QFileInfo MocFileView::fileInfo() const
{
   return m_fileInfo;
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

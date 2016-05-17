/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/FileViewInterface.h"

void FileViewInterface::setFileState(FileState state)
{
   Q_UNUSED(state);
}

void FileViewInterface::setFileInfo(const QFileInfo &fileInfo)
{
   Q_UNUSED(fileInfo);
}

FileViewInterface::Features FileViewInterface::viewFeatures() const
{
   return FileViewInterface::NoFeature;
}

void FileViewInterface::appendLine(const QString &line)
{
   Q_UNUSED(line);
}

void FileViewInterface::appendLines(const QStringList &lines)
{
   Q_UNUSED(lines);
}

void FileViewInterface::clearTextView()
{
}

void FileViewInterface::setLineHighlightingRules(const QList<HighlightingRule> &rules)
{
   Q_UNUSED(rules)
}

void FileViewInterface::setWordHighlighingRules(const QList<HighlightingRule> &rules)
{
   Q_UNUSED(rules)
}

QPointer<QWidget> FileViewInterface::widget() const
{
   return QPointer<QWidget>();
}


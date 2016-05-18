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

/*!
 * \brief FileViewInterface::setHighlightingRules
 * Set the highlightin rules for this view. As line rules have to be applied first before
 * word rules are applied, these rules are dependent. This is the reason why this method
 * takes both types of rules as parameters.
 * \param lineRules
 * \param wordRules
 */
void FileViewInterface::setHighlightingRules(const QList<HighlightingRule> &lineRules,
                                             const QList<HighlightingRule> &wordRules)
{
   Q_UNUSED(lineRules)
   Q_UNUSED(wordRules)
}

QPointer<QWidget> FileViewInterface::widget() const
{
   return QPointer<QWidget>();
}


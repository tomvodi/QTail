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

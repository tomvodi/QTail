/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/FileViewInterface.h"

class FileViewInterfacePrivate
{
public:
   QFileInfo fileInfo;
};

void FileViewInterface::setFileState(FileState state)
{
   Q_UNUSED(state);
}

FileViewInterface::FileViewInterface(QObject *parent)
      : QObject(parent),
        d(new FileViewInterfacePrivate)
{
}

FileViewInterface::~FileViewInterface()
{
   delete d;
}

void FileViewInterface::setFileInfo(const QFileInfo &fileInfo)
{
   d->fileInfo = fileInfo;
}

QFileInfo FileViewInterface::fileInfo() const
{
   return d->fileInfo;
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

/*!
 * \brief FileViewInterface::readCompleteFileUntil
 * If a file is opened, this method will be called on the view in order to read the complete file
 * until a maximum length.
 * \param maxLength
 */
void FileViewInterface::readCompleteFileUntil(qint64 maxLength)
{
   Q_UNUSED(maxLength);
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

/*!
 * \brief FileViewInterface::setFileActive
 * Set the active state of of a file. E.g. if the file is now the current file in the view,
 * it is active.
 * \param active
 */
void FileViewInterface::setFileActive(bool active)
{
   Q_UNUSED(active)
}


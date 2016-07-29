/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include "include/FileWatcherInterface.h"

FileWatcherInterface::FileWatcherInterface(QObject *parent)
   : QObject(parent)
{
}

void FileWatcherInterface::setFilePath(const QString &filePath)
{
   m_filePath = filePath;
}

QString FileWatcherInterface::filePath() const
{
   return m_filePath;
}

int FileWatcherInterface::updateInterval() const
{
    return m_updateIntervalMs;
}

void FileWatcherInterface::setUpdateInterval(int updateInterval)
{
    m_updateIntervalMs = updateInterval;
}

qint64 FileWatcherInterface::sizeOffset() const
{
    return m_sizeOffset;
}

/*!
 * \brief FileWatcherInterface::setSizeOffset
 * A size offset is used to signalize the file watcher that the first part of the file was
 * already read from the beginning. The first sizeChanged signal will contain the oldSize
 * paramet == sizeOffset.
 */
void FileWatcherInterface::setSizeOffset(const qint64 &sizeOffset)
{
    m_sizeOffset = sizeOffset;
}

/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDebug>

#include <QFileSystemWatcher>
#include <QFileInfo>

#include "FileWatcher.h"

FileWatcher::FileWatcher(QObject *parent)
    : QObject(parent),
      m_fileSystemWatcher(new QFileSystemWatcher(this))
{
    createConnections();
}

void FileWatcher::createConnections()
{

}

void FileWatcher::setFilePath(const QString &filePath)
{
    if (m_fileSystemWatcher->files().count() ||
            filePath.isEmpty() ||
            !QFile::exists(filePath)) {
        return;
    }

    m_fileSystemWatcher->addPath(filePath);
    m_fileInfo.setFile(filePath);

    // Read a file info value once, so that the file info cache is populated
    // with the actual informations.
    m_fileInfo.size();

    connect(m_fileSystemWatcher, &QFileSystemWatcher::fileChanged,
            this, &FileWatcher::fileHasChanged);
}

QString FileWatcher::filePath() const
{
    QString path;

    if (m_fileSystemWatcher->files().count()) {
        path = m_fileSystemWatcher->files().at(0);
    }

    return path;
}

void FileWatcher::fileHasChanged()
{
    if (m_fileInfo.fileName().isEmpty()) {
        return;
    }

    qint64 oldSize = m_fileInfo.size();
    m_fileInfo.refresh();

    if (!m_fileInfo.exists()) {
        emit fileRemoved();
        return;
    }

    qint64 newSize = m_fileInfo.size();
    if (newSize != oldSize) {
        emit sizeChanged(oldSize, newSize);
    }
}

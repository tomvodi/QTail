/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QFileInfo>
#include <QObject>

class QFileSystemWatcher;

class FileWatcher : public QObject
{
    Q_OBJECT
public:
    explicit FileWatcher(QObject *parent = 0);

    void setFilePath(const QString &filePath);
    QString filePath() const;

signals:
    void sizeChanged();

private slots:
    void fileHasChanged();

private:
    void createConnections();
    QFileSystemWatcher *m_fileSystemWatcher;
    QFileInfo m_fileInfo;
};

#endif // FILEWATCHER_H

/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILEREADLOGIC_H
#define FILEREADLOGIC_H

#include <QObject>
#include <QFileInfo>
#include <QPointer>

class FileWatcherInterface;

/*!
 * \brief The FileReadLogic class
 * This class handles when to completely reload a file or when to simply read the appended lines.
 */
class FileReadLogic : public QObject
{
    Q_OBJECT
public:
    FileReadLogic(QObject *parent=0);
    ~FileReadLogic();

    void setFileWatcher(FileWatcherInterface *fileWatcher);

private slots:
    void sizeChanged(qint64 oldSize, qint64 newSize);
    void fileRemoved();

signals:
    void fileCleared();
    void linesAppended(const QStringList &lines);

private:
    QPointer<FileWatcherInterface> m_fileWatcher;
    QFile *m_file;
};

#endif // FILEREADLOGIC_H

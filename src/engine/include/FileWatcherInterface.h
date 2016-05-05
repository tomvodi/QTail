/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef FILEWATCHERINTERFACE_H
#define FILEWATCHERINTERFACE_H

#include <QObject>

class FileWatcherInterface : public QObject
{
   Q_OBJECT
public:
   explicit FileWatcherInterface(QObject *parent = 0);

   virtual void setFilePath(const QString &filePath);
   QString filePath() const;

signals:
   void sizeChanged(qint64 oldSize, qint64 newSize);
   void fileRemoved();

private:
   QString m_filePath;
};

#endif // FILEWATCHERINTERFACE_H

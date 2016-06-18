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

   QString filePath() const;
   virtual void setFilePath(const QString &filePath);

   int updateInterval() const;
   virtual void setUpdateInterval(int updateInterval);

signals:
   void sizeChanged(qint64 oldSize, qint64 newSize);
   void fileRemoved();

private:
   QString m_filePath;
   int m_updateIntervalMs = 250;
};

#endif // FILEWATCHERINTERFACE_H

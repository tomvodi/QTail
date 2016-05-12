/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef MOCFILEWATCHER_H
#define MOCFILEWATCHER_H

#include <QObject>
#include <include/FileWatcherInterface.h>

class MocFileWatcher : public FileWatcherInterface
{
   Q_OBJECT
public:
   explicit MocFileWatcher(QObject *parent = 0);

   // FileWatcherInterface interface
   void setFilePath(const QString &filePath) override;
};

#endif // MOCFILEWATCHER_H

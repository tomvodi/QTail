/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef RELOADAPPENDLOGIC_H
#define RELOADAPPENDLOGIC_H

#include <QObject>
#include <QFileInfo>
#include <QPointer>

class FileWatcherInterface;

/*!
 * \brief The ReloadAppendLogic class
 * This class handles when to completely reload a file and when to simply append text to a file view.
 */
class ReloadAppendLogic : public QObject
{
   Q_OBJECT
public:
   ReloadAppendLogic(QObject *parent=0);
   ~ReloadAppendLogic();

   void setFileWatcher(FileWatcherInterface *fileWatcher);

private slots:
   void sizeChanged(qint64 oldSize, qint64 newSize);
   void fileRemoved();

signals:
   void fileCleared();
   void lineAppended(const QString &line);
   void linesAppended(const QStringList &lines);

private:
   QPointer<FileWatcherInterface> m_fileWatcher;
   QFile *m_file;
   qint64 m_oldSize = 0;
};

#endif // RELOADAPPENDLOGIC_H

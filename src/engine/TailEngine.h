/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#ifndef TAILENGINE_H
#define TAILENGINE_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QFileInfo>
#include <QSharedPointer>

class FileReadLogic;
class FileViewInterface;
class FileWatcher;

typedef QSharedPointer<FileViewInterface> FileView;
typedef QList<FileView> FileViews;

uint qHash(const QFileInfo &fileInfo);

/*!
 * \brief The TailEngine class
 * The TailEngine encapsulates the tracking of file changes.
 */
class TailEngine : public QObject
{
   Q_OBJECT
public:
   explicit TailEngine(QObject *parent = 0);

   void addFiles(const QFileInfo &file, const FileViews &views);
   void addFile(const QFileInfo &file, const FileView &view);
   void removeFile(const QFileInfo &file);
   void reloadFile(const QFileInfo &file);

private:
   class FileContext
   {
   public:
      FileContext() {}
      ~FileContext() {}

      QFileInfo fileInfo() const;
      void setFileInfo(const QFileInfo &fileInfo);

      FileWatcher *fileWatcher() const;
      void setFileWatcher(FileWatcher *fileWatcher);

      FileViews fileViews() const;
      void setFileViews(const FileViews &fileViews);
      void addFileView(const FileView &fileView);

      FileReadLogic *fileReadLogic() const;
      void setFileReadLogic(FileReadLogic *fileReadLogic);

   private:
      QFileInfo m_fileInfo;
      FileViews m_fileViews;
      FileWatcher *m_fileWatcher;
      FileReadLogic *m_fileReadLogic;
   };

   FileContext fileContextOfFile(const QFileInfo &file);
   QHash<QFileInfo, FileContext> m_fileContexts;
   void setFileContextOfFile(const QFileInfo &file, FileContext context);
   void handleChangedFileSize(const QFileInfo &file, qint64 oldSize, qint64 newSize);
   void handleChangedFileContent(const QFileInfo &file);
   void handleRemovedFile(const QFileInfo &file);
};

#endif // TAILENGINE_H

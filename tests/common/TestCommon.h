/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */
#ifndef TESTCOMMON_H
#define TESTCOMMON_H

#include <QFont>
#include <QString>
#include <QCoreApplication>
#include <QDir>

class TestCommon
{
public:
   TestCommon();
   enum class FileAction {
      AppendOnly,
      ClearFile
   };

   static QString generateExistingFileInPath(const QString &fileName,
                                             const QString &path=QCoreApplication::applicationDirPath());
   static void appendLinesToFile(const QString &fileName, const QStringList &lines,
                                 FileAction fileAction=FileAction::AppendOnly);
   static void waitMsecs(quint32 mSecs);

   static QFont testFont();

   static void clearDir(const QDir &dir);
};

#endif // TESTCOMMON_H

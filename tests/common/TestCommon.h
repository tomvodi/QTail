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

class TestCommon
{
public:
   TestCommon();
   enum class FileAction {
      AppendOnly,
      ClearFile
   };

   static QString generateExistingFilePath(const QString &fileName);
   static void appendLinesToFile(const QString &fileName, const QStringList &lines,
                                 FileAction fileAction=FileAction::AppendOnly);
   static void waitMsecs(quint32 mSecs);

   static QFont testFont();
};

#endif // TESTCOMMON_H

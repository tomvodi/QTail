/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QCoreApplication>

#include "TestCommon.h"

TestCommon::TestCommon()
{
}

QString TestCommon::generateExistingFilePath(const QString &fileName)
{
   QString filePath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(fileName);
   QFile file(filePath);
   file.open(QIODevice::WriteOnly | QIODevice::Truncate);
   file.close();

   return filePath;
}

void TestCommon::appendLinesToFile(const QString &fileName, const QStringList &lines, FileAction fileAction)
{
   QFile outFile(fileName);
   QIODevice::OpenMode openMode = QIODevice::WriteOnly;
   if (fileAction == FileAction::AppendOnly) {
      openMode |= QIODevice::Append;
   }

   if (!outFile.open(openMode)) {
      qWarning() << "Failed opening file for reading";
   }
   QTextStream stream(&outFile);

   foreach (const QString &line, lines) {
      stream << line;
   }

   stream.flush();
   outFile.close();
   waitMsecs(5);
}

void TestCommon::waitMsecs(quint32 mSecs)
{
   QCoreApplication::processEvents();

   QEventLoop loop;
   QTimer::singleShot(mSecs, &loop, SLOT(quit()));
   loop.exec();
}

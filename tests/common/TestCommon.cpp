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
#include <QFontDatabase>

#include "TestCommon.h"

TestCommon::TestCommon()
{
}

QString TestCommon::generateExistingFileInPath(const QString &fileName, const QString &path)
{
   QString filePath = QDir(path).absoluteFilePath(fileName);
   QFile file(filePath);
   file.open(QIODevice::WriteOnly | QIODevice::Truncate);
   file.close();

   waitMsecs(10);

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

QFont TestCommon::testFont()
{
   QFontDatabase database;
   QStringList fonts = database.families();

   QFont font;
   if (fonts.count() > 3) {
      font = QFont(fonts.at(2));
   }

   font.setPointSize(8); // Set integer value for pointsize that is selectable in the gui
   return font;
}

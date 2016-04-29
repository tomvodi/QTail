/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QDir>
#include <QFile>
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

void TestCommon::waitMsecs(quint32 mSecs)
{
   QCoreApplication::processEvents();

   QEventLoop loop;
   QTimer::singleShot(mSecs, &loop, SLOT(quit()));
   loop.exec();
}

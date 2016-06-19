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
#include <QFontComboBox>

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
   // Using a monospaced font from the QFontCombobox
   // because a QFontComboBox is always used to select a font and the testFont must
   // return a font that is selectable in a QFontComboBox with only monospaced fonts
   QFontComboBox comboBox;
   comboBox.setFontFilters(QFontComboBox::MonospacedFonts);

   QFont font;
   if (comboBox.count() > 3) {
      comboBox.setCurrentIndex(1);
      font = comboBox.currentFont();
   }

   font.setPointSize(8); // Set integer value for pointsize that is selectable in the gui
   return font;
}

void TestCommon::clearDir(const QDir &dir)
{
   QDir emptyDir(dir);
   emptyDir.setNameFilters(QStringList() << "*");
   emptyDir.setFilter(QDir::Files);
   foreach(QString dirFile, emptyDir.entryList()) {
      emptyDir.remove(dirFile);
   }
}

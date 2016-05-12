/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */

#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <TestCommon.h>

#include <MocFileWatcher.h>
#include <FileReadLogic.h>

class FileReadLogicTest : public QObject
{
   Q_OBJECT

public:
   FileReadLogicTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testAppendLineToEmptyFile();
};

FileReadLogicTest::FileReadLogicTest()
{
}

void FileReadLogicTest::initTestCase()
{
}

void FileReadLogicTest::cleanupTestCase()
{
}

/*!
 * \brief FileReadLogicTest::testAppendLineToEmptyFile
 * Appending lines to an empty file, should result in clear signal to get attached views that
 * probably already show some text to clear before append the line.
 */
void FileReadLogicTest::testAppendLineToEmptyFile()
{
   QString testFile = TestCommon::generateExistingFilePath("testAppendLineToEmptyFile.log");
   QScopedPointer<MocFileWatcher> fileWatcher(new MocFileWatcher);
   fileWatcher->setFilePath(testFile);

   FileReadLogic readLogic;
   readLogic.setFileWatcher(fileWatcher.data());

   QFile outFile(testFile);
   QVERIFY(outFile.open(QIODevice::WriteOnly));
   QTextStream stream(&outFile);

   QString testLine("This is the first line");
   stream << testLine;
   stream.flush();
   outFile.close();

   QFileInfo testFileInfo(testFile);
   QSignalSpy clearSpy(&readLogic, SIGNAL(fileCleared()));
   QSignalSpy appendSpy(&readLogic, SIGNAL(linesAppended(QStringList)));

   fileWatcher->sizeChanged(0, testFileInfo.size());

   QVERIFY2(clearSpy.count() == 1, "Clear signals wasn't' emitted after only appending line to empty file.");
   QVERIFY2(appendSpy.count() == 1, "Clear signals was emitted after only appending line to file.");
}

QTEST_MAIN(FileReadLogicTest)

#include "tst_FileReadLogicTest.moc"

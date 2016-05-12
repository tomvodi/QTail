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
   void testAppendLineToNonEmptyFile();
   void testAppendLineToShrinkedFile();
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

   QString testLine("This is the first line");
   TestCommon::appendLinesToFile(testFile, {testLine});

   QFileInfo testFileInfo(testFile);
   QSignalSpy clearSpy(&readLogic, SIGNAL(fileCleared()));
   QSignalSpy appendSpy(&readLogic, SIGNAL(linesAppended(QStringList)));

   fileWatcher->sizeChanged(0, testFileInfo.size());

   QVERIFY2(clearSpy.count() == 1, "Clear signals wasn't emitted after only appending line to empty file.");
   QVERIFY2(appendSpy.count() == 1, "Lines appended signal wasn't emitted after appending line to empty file.");
   QString appendedLine = appendSpy.at(0).at(0).toStringList().first();
   QVERIFY2(appendedLine == testLine, "The appended line doesn't match.");
}

/*!
 * \brief FileReadLogicTest::testAppendLineToNonEmptyFile
 * Appending lines ot a non empty file should NOT result in clear signal
 */
void FileReadLogicTest::testAppendLineToNonEmptyFile()
{
   QString testFile = TestCommon::generateExistingFilePath("testAppendLineToNonEmptyFile.log");
   // Add file content before file watcher is active
   QStringList fileContent({"First line\n", "Second line\n", "Third line\n"});
   TestCommon::appendLinesToFile(testFile, fileContent);

   QScopedPointer<MocFileWatcher> fileWatcher(new MocFileWatcher);
   fileWatcher->setFilePath(testFile);

   FileReadLogic readLogic;
   readLogic.setFileWatcher(fileWatcher.data());

   QFileInfo testFileInfo(testFile);
   int fileSizeBeforeAppendNewContent = testFileInfo.size();
   QSignalSpy clearSpy(&readLogic, SIGNAL(fileCleared()));
   QSignalSpy appendSpy(&readLogic, SIGNAL(linesAppended(QStringList)));

   // Add file content after file watcher is active
   QString newLine1("First new line\n");
   QString newLine2("Second new line");
   TestCommon::appendLinesToFile(testFile, {newLine1, newLine2});

   testFileInfo.refresh();
   int fileSizeAfterNewContent = testFileInfo.size();
   Q_ASSERT(fileSizeBeforeAppendNewContent < fileSizeAfterNewContent);

   fileWatcher->sizeChanged(fileSizeBeforeAppendNewContent, fileSizeAfterNewContent);

   QVERIFY2(clearSpy.count() == 0, "Clear signals wasn emitted after appending line to NON empty file.");
   QVERIFY2(appendSpy.count() == 1, "Lines appended signal wasn't emitted after appending lines to NON empty file.");
   QStringList appendedLines = appendSpy.at(0).at(0).toStringList();

   QVERIFY2(appendedLines.count() != 0, "No lines were emitted for appended lines");
   QVERIFY2(appendedLines.count() <= 2, "Too many lines were emitted for appended lines.");
   QVERIFY2(appendedLines.count() == 2, "Not all lines were emitted for appended lines");
   QVERIFY2(appendedLines.first() == newLine1.trimmed(), "The first appended line isn't the first emitted line");
   QVERIFY2(appendedLines.last() == newLine2.trimmed(), "The second appended line isn't the second emitted line");
}

/*!
 * \brief FileReadLogicTest::testAppendLineToShrinkedFile
 * First, the file
 * If the file size has shrinked, the content has definitely changed.
 * So a clear file signal must be emitted at first.
 */
void FileReadLogicTest::testAppendLineToShrinkedFile()
{
   QString testFile = TestCommon::generateExistingFilePath("testAppendLineToShrinkedFile.log");
   // Add file content before file watcher is active
   QString fileLine1("First line\n");
   QString fileLine2("Second line\n");
   QStringList fileContent({fileLine1, fileLine2, "Third line\n"});
   TestCommon::appendLinesToFile(testFile, fileContent);

   QFileInfo testFileInfo(testFile);
   int fileSizeBeforeRemovingLine = testFileInfo.size();

   QScopedPointer<MocFileWatcher> fileWatcher(new MocFileWatcher);
   fileWatcher->setFilePath(testFile);

   FileReadLogic readLogic;
   readLogic.setFileWatcher(fileWatcher.data());

   // Simulate a deletion of the last line
   QStringList newFileContent({fileLine1, fileLine2});
   TestCommon::appendLinesToFile(testFile, newFileContent, TestCommon::FileAction::ClearFile);

   QSignalSpy clearSpy(&readLogic, SIGNAL(fileCleared()));
   QSignalSpy appendSpy(&readLogic, SIGNAL(linesAppended(QStringList)));

   testFileInfo.refresh();
   int fileSizeAfterRemoveLine = testFileInfo.size();
   Q_ASSERT(fileSizeBeforeRemovingLine > fileSizeAfterRemoveLine);

   fileWatcher->sizeChanged(fileSizeBeforeRemovingLine, fileSizeAfterRemoveLine);

   QVERIFY2(clearSpy.count() == 1, "Clear signals wasn emitted after removing line from NON empty file.");
   QVERIFY2(appendSpy.count() == 1, "Lines appended signal wasn't emitted removing lines from NON empty file.");
   QStringList appendedLines = appendSpy.at(0).at(0).toStringList();

   QVERIFY2(appendedLines.count() != 0, "No lines were emitted for appended lines");
   QVERIFY2(appendedLines.count() <= 2, "Too many lines were emitted for appended lines.");
   QVERIFY2(appendedLines.count() == 2, "Not all lines were emitted for appended lines");
   QVERIFY2(appendedLines.first() == fileLine1.trimmed(), "The first appended line isn't the first emitted line");
   QVERIFY2(appendedLines.last() == fileLine2.trimmed(), "The second appended line isn't the second emitted line");
}

QTEST_MAIN(FileReadLogicTest)

#include "tst_FileReadLogicTest.moc"

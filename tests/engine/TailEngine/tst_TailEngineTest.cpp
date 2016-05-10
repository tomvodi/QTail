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

#include <engine/TailEngine.h>

#include <MocFileView.h>
#include <TestCommon.h>

class TailEngineTest : public QObject
{
   Q_OBJECT

public:
   TailEngineTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testFileStateAddedLines();
   void testFileStateViewHasNoStateFeature();
   void testFileStateRemovedFile();
   void testFileStateRemovedLines();
   void testLinesAddedLinesToFile();
   void testLinesViewHasNoTextFeature();
   void testLinesOpenNonEmptyFile();
   void testLinesInitialPopulatingView();
};

TailEngineTest::TailEngineTest()
{
}

void TailEngineTest::initTestCase()
{
}

void TailEngineTest::cleanupTestCase()
{
}

void TailEngineTest::testFileStateAddedLines()
{
   QString filePath = TestCommon::generateExistingFilePath(QStringLiteral("testLineAddedSignal.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView;
   fileView->setViewFeatures(FileViewInterface::HasStateView);
   FileView sharedFileView(fileView);

   engine.addFile(QFileInfo(filePath), {sharedFileView});

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);

   QVERIFY2(fileView->fileStateWasSetByInterfaceMethod() == false, "File state was set by engine before writing anything to file.");
   QVERIFY2(fileView->fileState() == FileState::FileInSync, "Wrong default file state");

   stream << "Test text";
   stream.flush();
   TestCommon::waitMsecs(100);

   QVERIFY2(fileView->fileStateWasSetByInterfaceMethod() == true, "File state wasn't set by engine.");
   QVERIFY2(fileView->fileState() == FileState::FileHasChanged, "File state wasn't set correctly.");
}

void TailEngineTest::testFileStateViewHasNoStateFeature()
{
   QString filePath = TestCommon::generateExistingFilePath(QStringLiteral("testFileStateViewHasNoStateFeature.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView;
   fileView->setViewFeatures(FileViewInterface::NoFeature);  // View has no state feature
   FileView sharedFileView(fileView);

   engine.addFiles(QFileInfo(filePath), {sharedFileView});

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);
   stream << "Test text";
   stream.flush();

   TestCommon::waitMsecs(100);

   QVERIFY2(fileView->fileStateWasSetByInterfaceMethod() == false, "File state was set by engine despite no state feature.");
   QVERIFY2(fileView->fileState() == FileState::FileInSync, "File state wasn't set correctly.");
}

void TailEngineTest::testFileStateRemovedFile()
{
   QString filePath = TestCommon::generateExistingFilePath(QStringLiteral("testFileStateRemovedFile.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView;
   fileView->setViewFeatures(FileViewInterface::HasStateView);
   FileView sharedFileView(fileView);

   engine.addFiles(QFileInfo(filePath), {sharedFileView});

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);
   stream << "Test text";
   stream.flush();
   outFile.close();
   TestCommon::waitMsecs(100);

   Q_ASSERT(fileView->fileState() == FileState::FileHasChanged);

   QFile::remove(filePath);
   TestCommon::waitMsecs(100);
   QVERIFY2(fileView->fileState() == FileState::FileError, "File state not error for removed file.");
}

void TailEngineTest::testFileStateRemovedLines()
{
   QString filePath = TestCommon::generateExistingFilePath(QStringLiteral("testFileStateNewLines.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView;
   fileView->setViewFeatures(FileViewInterface::HasStateView);
   FileView sharedFileView(fileView);

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);
   stream << "Test text\n" << "Test line 2\n";
   stream.flush();
   TestCommon::waitMsecs(100);

   // Add file to engine after there are already two lines in it
   engine.addFiles(QFileInfo(filePath), {sharedFileView});

   // Now remove last line
   outFile.resize(0);
   stream << "TestText";
   stream.flush();
   TestCommon::waitMsecs(100);

   QVERIFY2(fileView->fileState() == FileState::FileHasChanged, "File state is wrong for removed lines.");
}

void TailEngineTest::testLinesAddedLinesToFile()
{
   QString line1(QStringLiteral("This is the first text line\n"));
   QString line2(QStringLiteral("This is the second text line\n"));
   QString filePath = TestCommon::generateExistingFilePath(QStringLiteral("testLinesAddedLines.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView;
   fileView->setViewFeatures(FileViewInterface::HasTextView);
   fileView->appendLine("This line should be cleared.");
   FileView sharedFileView(fileView);

   engine.addFile(QFileInfo(filePath), {sharedFileView});

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);

   stream << line1 << line2;
   stream.flush();
   TestCommon::waitMsecs(100);

   QVERIFY2(fileView->textViewLines().count() > 1, "No text line was added by engine.");
   QVERIFY2(fileView->textViewLines().count() < 3, "Text view wasn't cleared.");
   QVERIFY2(fileView->textViewLines().count() == 2, "No the right count of text lines was added by engine.");
   QVERIFY2(fileView->textViewLines().first() == line1.trimmed(), "First line in file isn't first line in view.");
   QVERIFY2(fileView->textViewLines().at(1) == line2.trimmed(), "Second line in file isn't second line in view.");
}

void TailEngineTest::testLinesViewHasNoTextFeature()
{
   QString filePath = TestCommon::generateExistingFilePath(QStringLiteral("testLinesViewHasNoTextFeature.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView;
   fileView->setViewFeatures(FileViewInterface::NoFeature);  // View has no text feature
   FileView sharedFileView(fileView);

   engine.addFiles(QFileInfo(filePath), {sharedFileView});

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);
   stream << "Test text";
   stream.flush();

   TestCommon::waitMsecs(100);

   QVERIFY2(fileView->textViewLines().count() == 0, "View text was set by engine despite no text feature.");
}

void TailEngineTest::testLinesOpenNonEmptyFile()
{
   // Open non empty file
   // -> Clear
   // -> appendLines
}

void TailEngineTest::testLinesInitialPopulatingView()
{
   QString filePath = TestCommon::generateExistingFilePath(QStringLiteral("testLinesInitialPopulatingView.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView;
   fileView->setViewFeatures(FileViewInterface::HasTextView);  // View has no text feature
   FileView sharedFileView(fileView);

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);
   stream << "Test line 1\n" << "Test line 2";
   stream.flush();
   TestCommon::waitMsecs(100);

   engine.addFiles(QFileInfo(filePath), {sharedFileView});

   TestCommon::waitMsecs(100);

   QVERIFY2(fileView->textViewLines().count() == 2, "View text wasn't set by initially adding file.");
}

QTEST_MAIN(TailEngineTest)

#include "tst_TailEngineTest.moc"

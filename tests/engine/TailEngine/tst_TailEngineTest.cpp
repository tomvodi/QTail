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
#include <FileWatcher.h>

#include <engine/TailEngine.h>

#include <MocFileView.h>
#include <MocFileWatcher.h>
#include <TestCommon.h>

#include <include/FilterGroup.h>

class TailEngineTest : public QObject
{
   Q_OBJECT

public:
   TailEngineTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testFileStateAddedLines();
   void testAddFileWithFileSizeOffset();
   void testFileStateViewHasNoStateFeature();
   void testFileStateRemovedFile();
   void testFileStateRemovedLines();
   void testSetFileInfoCallOnAddFile();
   void testReadUntilCallInAddFile();
   void testLinesAddedLinesToFile();
   void testLinesViewHasNoTextFeature();
   void testSetFileActive();
   void testRemoveFile();
   void testSetTextViewSettings();
   void testSetActiveFilters();
   void testSetActiveFiltersBeforeOpenFile();
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
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testLineAddedSignal.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
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

/*!
 * \brief TailEngineTest::testAddFileWithFileSizeOffset
 * Adding a file which has already content should result in setting the offset to the FileWatcher.
 */
void TailEngineTest::testAddFileWithFileSizeOffset()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testAddFileWithFileSizeOffset.log"));
   TailEngine engine;

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);
   stream << "Test text";
   stream.flush();
   outFile.close();
   Q_ASSERT(outFile.size());

   TestCommon::waitMsecs(100);

   MocFileView *fileView = new MocFileView(this);
   fileView->setViewFeatures(FileViewInterface::HasTextView);
   FileView sharedFileView(fileView);

   engine.addFile(QFileInfo(filePath), {sharedFileView});

   qint64 offsetSize = outFile.size();
   QVERIFY2(fileView->readUntilMaxLength() == offsetSize, "readUntilMaxLength wasn't called with correct size.");
   TailEngine::FileContext textFileContext = engine.fileContextOfFile(filePath);
   QVERIFY2(textFileContext.fileWatcher()->sizeOffset() == offsetSize, "Size offset wasn't set in FileWatcher");
}

void TailEngineTest::testFileStateViewHasNoStateFeature()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testFileStateViewHasNoStateFeature.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
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
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testFileStateRemovedFile.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
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
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testFileStateNewLines.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
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

void TailEngineTest::testSetFileInfoCallOnAddFile()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testReadUntilCallInAddFile.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
   fileView->setViewFeatures(FileViewInterface::HasTextView);
   FileView sharedFileView(fileView);

   QFileInfo fileInfo(filePath);
   engine.addFiles(fileInfo, {sharedFileView});

   QVERIFY2(fileView->fileInfo() == fileInfo, "File info wasn't set on adding file");
}

/*!
 * \brief TailEngineTest::testReadUntilCallInAddFile
 * If a file is added to the engine which has already content, the engine must init text views
 * to read the file until the current size.
 */
void TailEngineTest::testReadUntilCallInAddFile()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testReadUntilCallInAddFile.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
   fileView->setViewFeatures(FileViewInterface::HasTextView);
   FileView sharedFileView(fileView);

   QString testText1("Test text1\nTest line 2\n");
   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);
   stream << testText1;
   stream.flush();
   TestCommon::waitMsecs(100);

   engine.addFiles(QFileInfo(filePath), {sharedFileView});

   QVERIFY2(fileView->readUntilMaxLength() != -1, "readCompleteFileUntil wasn't called on file");
   QVERIFY2(fileView->readUntilMaxLength() == testText1.length(), "readCompleteFileUntil wasn't called with correct file size");
}

void TailEngineTest::testLinesAddedLinesToFile()
{
   QString line1(QStringLiteral("This is the first text line\n"));
   QString line2(QStringLiteral("This is the second text line\n"));
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testLinesAddedLines.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
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
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testLinesViewHasNoTextFeature.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
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

void TailEngineTest::testSetFileActive()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testLinesViewHasNoTextFeature.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
   fileView->setViewFeatures(FileViewInterface::NoFeature);
   FileView sharedFileView(fileView);

   engine.addFiles(QFileInfo(filePath), {sharedFileView});

   engine.setFileActive(filePath, true);

   QVERIFY2(fileView->fileActive() == true, "File active state wasn't set on file");
}

void TailEngineTest::testRemoveFile()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testLinesViewHasNoTextFeature.log"));
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
   fileView->setViewFeatures(FileViewInterface::NoFeature);
   FileView sharedFileView(fileView);

   QFileInfo fileInfo(filePath);
   engine.addFiles(fileInfo, {sharedFileView});
   Q_ASSERT(engine.m_fileContexts.contains(fileInfo));

   engine.removeFile(fileInfo);

   QVERIFY2(engine.m_fileContexts.isEmpty(), "File context wasn't removed for file");
}

void TailEngineTest::testSetTextViewSettings()
{
   QString textFilePath = TestCommon::generateExistingFileInPath(QStringLiteral("testSetTextViewFontTextView.log"));
   QString noTextFilePath = TestCommon::generateExistingFileInPath(QStringLiteral("testSetTextViewFontNoTextView.log"));
   TailEngine engine;

   MocFileView *textFileView = new MocFileView(this);
   textFileView->setViewFeatures(FileViewInterface::HasTextView);
   FileView sharedTextFileView(textFileView);

   MocFileView *noTextFileView = new MocFileView(this);
   noTextFileView->setViewFeatures(FileViewInterface::HasStateView);
   FileView sharedFileView(noTextFileView);

   engine.addFile(QFileInfo(textFilePath), sharedTextFileView);
   engine.addFile(QFileInfo(noTextFilePath), sharedFileView);

   int testUpdateInterval = 1234;
   TextViewSettings settings;
   settings.setFont(TestCommon::testFont());
   settings.setLineWrapOn(!textFileView->textViewSettings().lineWrapOn());
   settings.setUpdateInterval(testUpdateInterval);

   Q_ASSERT(settings.font() != textFileView->textViewSettings().font());
   Q_ASSERT(settings.font() != noTextFileView->textViewSettings().font());

   engine.setTextViewSettings(settings);

   QVERIFY2(textFileView->textViewSettings() == settings, "Text view settins wasn't set on text view.");
   QVERIFY2(noTextFileView->textViewSettings() != settings, "Text view settings were set on nont text view.");

   TailEngine::FileContext textFileContext = engine.fileContextOfFile(textFilePath);
   FileWatcherInterface *textFileWatcher = textFileContext.fileWatcher();
   Q_ASSERT(textFileWatcher);
   QVERIFY2(textFileWatcher->updateInterval() == testUpdateInterval, "Update interval wasn't set on filewatcher of file");

   // Now test if a newly added text view gets the settings
   textFileView = new MocFileView(this);
   textFileView->setViewFeatures(FileViewInterface::HasTextView);
   sharedTextFileView = FileView(textFileView);
   textFilePath = TestCommon::generateExistingFileInPath(QStringLiteral("testSetTextViewFontTextViewNew.log"));

   // Set new update interval to check if it will be set.
   engine.addFile(QFileInfo(textFilePath), textFileView);
   QVERIFY2(textFileView->textViewSettings() == settings, "Text view settings weren't set on text view that was added after the settings were set to engine.");

   // Get the context of the new file
   textFileContext = engine.fileContextOfFile(textFilePath);
   textFileWatcher = textFileContext.fileWatcher();
   Q_ASSERT(textFileWatcher);

   QVERIFY2(textFileWatcher->updateInterval() == testUpdateInterval, "Update interval wasn't set on filewatcher of new added file");
}

/*!
 * \brief TailEngineTest::testSetActiveFilters
 * Setting active filters for an already added file should result in setting the filters in the view
 * and then a complete reread.
 */
void TailEngineTest::testSetActiveFilters()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testSetActiveFilters.log"));
   QFileInfo fileInfo(filePath);
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
   fileView->setViewFeatures(FileViewInterface::HasTextView);
   FileView sharedFileView(fileView);

   engine.addFile(fileInfo, {sharedFileView});

   MocFileWatcher *fileWatcher = new MocFileWatcher(this);
   TailEngine::FileContext textFileContext = engine.fileContextOfFile(fileInfo);
   delete textFileContext.fileWatcher();
   textFileContext.setFileWatcher(fileWatcher);
   engine.setFileContextOfFile(fileInfo, textFileContext);

   FilterRule activeRule("first text line");
   activeRule.setActive(true);
   FilterRule deactivatedRule("second text");
   deactivatedRule.setActive(false);

   // Reset readComplete state because this must be called in setActiveFiltersForFile
   fileView->readCompleteFileUntil(-1);

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);
   stream << "Test text";
   stream.flush();
   outFile.close();
   Q_ASSERT(outFile.size());

   TestCommon::waitMsecs(100);

   engine.setActiveFiltersForFile(fileInfo, {activeRule, deactivatedRule});

   qint64 offsetSize = outFile.size();
   QVERIFY2(fileView->activeFilterRules() == QList<FilterRule>({activeRule, deactivatedRule}),
            "FilterGroups weren't set");
   QVERIFY2(fileView->readUntilMaxLength() != -1, "readCompleteFileUntil wasn't called on file");
   QVERIFY2(fileView->readUntilMaxLength() == offsetSize, "readCompleteFileUntil wasn't called with correct size");

   QVERIFY2(fileWatcher->sizeOffset() == offsetSize, "Size offset wasn't set in FileWatcher");
}

/*!
 * \brief TailEngineTest::testSetActiveFiltersBeforeOpenFile
 * Set the active filters for a file before the file is added should result in opening the file
 * with the filter.
 */
void TailEngineTest::testSetActiveFiltersBeforeOpenFile()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testSetActiveFiltersBeforeOpenFile.log"));
   QFileInfo fileInfo(filePath);
   TailEngine engine;

   MocFileView *fileView = new MocFileView(this);
   fileView->setViewFeatures(FileViewInterface::HasTextView);
   FileView sharedFileView(fileView);

   FilterRule activeRule("first text line");
   activeRule.setActive(true);
   FilterRule deactivatedRule("second text");
   deactivatedRule.setActive(false);

   engine.setActiveFiltersForFile(fileInfo, {activeRule, deactivatedRule});
   engine.addFile(fileInfo, {sharedFileView});

   QVERIFY2(fileView->activeFilterRules() == QList<FilterRule>({activeRule, deactivatedRule}),
            "FilterGroups weren't set to view.");
}

QTEST_MAIN(TailEngineTest)

#include "tst_TailEngineTest.moc"

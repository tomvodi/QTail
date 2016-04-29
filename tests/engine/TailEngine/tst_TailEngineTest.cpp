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

QTEST_MAIN(TailEngineTest)

#include "tst_TailEngineTest.moc"

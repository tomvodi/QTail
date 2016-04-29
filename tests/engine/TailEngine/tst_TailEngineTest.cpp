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
    void testFileState();
    void testFileStateViewHasNoStateFeature();
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

void TailEngineTest::testFileState()
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
    QVERIFY2(fileView->fileState() == FileState::FileError, "Wrong default file state");

    stream << "Test text";
    stream.flush();
    TestCommon::waitMsecs(100);

    QVERIFY2(fileView->fileStateWasSetByInterfaceMethod() == true, "File state wasn't set by engine.");
    QVERIFY2(fileView->fileState() == FileState::FileHasNewLines, "File state wasn't set correctly.");

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
   QVERIFY2(fileView->fileState() == FileState::FileError, "File state wasn't set correctly.");
}

QTEST_MAIN(TailEngineTest)

#include "tst_TailEngineTest.moc"

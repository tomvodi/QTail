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
#include <QScopedPointer>
#include <QSignalSpy>
#include <QFile>
#include <QTextStream>

#include <engine/FileWatcher.h>
#include <TestCommon.h>

class FileWatcherTest : public QObject
{
    Q_OBJECT

public:
    FileWatcherTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testAddEmptyPath();
    void testSetGetFilePath();
    void testSizeChanged();
};

FileWatcherTest::FileWatcherTest()
{
}

void FileWatcherTest::initTestCase()
{
}

void FileWatcherTest::cleanupTestCase()
{
}

void FileWatcherTest::testAddEmptyPath()
{
    FileWatcher watcher;
    watcher.setFilePath("");
    QVERIFY2(watcher.filePath().isEmpty(), "Failed set empty filePath");
}

void FileWatcherTest::testSetGetFilePath()
{
    QString filePath = TestCommon::generateExistingFilePath(QStringLiteral("testSetGetFilePath.log"));

    FileWatcher watcher;
    watcher.setFilePath(filePath);
    QVERIFY2(watcher.filePath() == filePath, "Failed set/get filePath");
}

void FileWatcherTest::testSizeChanged()
{
    QString filePath = TestCommon::generateExistingFilePath(QStringLiteral("testLineAddedSignal.log"));

    QScopedPointer<FileWatcher> fileWatcher(new FileWatcher);
    QSignalSpy spy(fileWatcher.data(), SIGNAL(sizeChanged()));
    fileWatcher->setFilePath(filePath);

    QFile outFile(filePath);
    QVERIFY(outFile.open(QIODevice::WriteOnly));
    QTextStream stream(&outFile);

    QString testLine("This is the first line");
    stream << testLine;
    stream.flush();
    outFile.close();

    TestCommon::waitMsecs(100);

    QVERIFY2(spy.count() == 1, "Signal for changed size wasn't emitted.");
}

QTEST_MAIN(FileWatcherTest)

#include "tst_FileWatcherTest.moc"

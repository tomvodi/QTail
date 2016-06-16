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
   void testBaseImplementation();
   void testAddEmptyPath();
   void testSetGetFilePath();
   void testSizeChanged();
   void testFileCheckTimer();
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

void FileWatcherTest::testBaseImplementation()
{
   FileWatcher watcher;
   watcher.setFilePath("kdkdkdkd");
   QVERIFY2(!watcher.filePath().isEmpty(), "Base implementation of setFilePath wasn't called");
}

void FileWatcherTest::testAddEmptyPath()
{
   FileWatcher watcher;
   watcher.setFilePath("");
   QVERIFY2(watcher.filePath().isEmpty(), "Failed set empty filePath");
}

void FileWatcherTest::testSetGetFilePath()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testSetGetFilePath.log"));

   FileWatcher watcher;
   watcher.setFilePath(filePath);
   QVERIFY2(watcher.filePath() == filePath, "Failed set/get filePath");
}

void FileWatcherTest::testSizeChanged()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testSizeChanged.log"));

   QScopedPointer<FileWatcher> fileWatcher(new FileWatcher);
   QSignalSpy spy(fileWatcher.data(), SIGNAL(sizeChanged(qint64, qint64)));
   fileWatcher->setFilePath(filePath);

   QFile outFile(filePath);
   QVERIFY(outFile.open(QIODevice::WriteOnly));
   QTextStream stream(&outFile);

   QString testLine("This is the first line");
   stream << testLine;
   stream.flush();
   outFile.close();

   spy.wait();

   QVERIFY2(spy.count() == 1, "Signal for changed size wasn't emitted.");
}

void FileWatcherTest::testFileCheckTimer()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testSizeChanged.log"));

   QScopedPointer<FileWatcher> fileWatcher(new FileWatcher);

   // Block QFileSystemWatcher's signal so the sizeChanged signal of FileWatcher will only be
   // emitted by the timer event
   fileWatcher->m_fileSystemWatcher->blockSignals(true);

   QSignalSpy spy(fileWatcher.data(), SIGNAL(sizeChanged(qint64, qint64)));
   fileWatcher->setFilePath(filePath);

   QFile outFile(filePath);
   QVERIFY(outFile.open(QIODevice::WriteOnly));
   QTextStream stream(&outFile);

   QString testLine("This is the first line");
   stream << testLine;
   stream.flush();
   outFile.close();

   spy.wait(5000);

   QVERIFY2(spy.count() == 1, "Signal for changed size wasn't emitted by timer event.");
}

QTEST_MAIN(FileWatcherTest)

#include "tst_FileWatcherTest.moc"

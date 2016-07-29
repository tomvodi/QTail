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
   void testSetUpdateInterval();
   void testAddEmptyPath();
   void testSetGetFilePath();
   void testSizeChanged();
   void testFileCheckTimer();
   void testSizeOffset();
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

void FileWatcherTest::testSetUpdateInterval()
{
   FileWatcher watcher;
   watcher.setUpdateInterval(34215);
   QVERIFY2(watcher.updateInterval() == 34215, "Failed setting update interval. Maybe parent implementation not called.");
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

   // Test after setting update interval explicitly. First kill timer to check if it is
   // started with setUpdateInterval.
   fileWatcher->killTimer(fileWatcher->m_timerId);
   fileWatcher->m_timerId = 0;
   spy.clear();

   fileWatcher->setUpdateInterval(100);

   QVERIFY(outFile.open(QIODevice::WriteOnly));
   testLine = QStringLiteral("This is the second line");
   stream << testLine;
   stream.flush();
   outFile.close();

   spy.wait(5000);

   QVERIFY2(spy.count() == 1, "Signal wasn't emitted, after setting update interval explicitly.");
}

void FileWatcherTest::testSizeOffset()
{
   QString filePath = TestCommon::generateExistingFileInPath(QStringLiteral("testSizeOffset.log"));

   // Create a file with content so there is already an offset
   QFile outFile(filePath);
   QVERIFY(outFile.open(QIODevice::WriteOnly));
   QTextStream stream(&outFile);

   stream << "This is the first line\n" << "This is the second line\n";
   stream.flush();
   outFile.close();

   qint64 offsetFileSize = outFile.size();
   Q_ASSERT(offsetFileSize != 0);

   // Now simmulate that the file gets new content until FileWatcher was initialized
   QVERIFY(outFile.open(QIODevice::Append | QIODevice::Text));

   stream << "This is the last line";
   stream.flush();
   outFile.close();
   Q_ASSERT(outFile.size() > offsetFileSize);

   QScopedPointer<FileWatcher> fileWatcher(new FileWatcher);
   fileWatcher->setSizeOffset(offsetFileSize);

   // Block QFileSystemWatcher's signal so the sizeChanged signal of FileWatcher will only be
   // emitted by the timer event
   fileWatcher->m_fileSystemWatcher->blockSignals(true);

   QSignalSpy spy(fileWatcher.data(), SIGNAL(sizeChanged(qint64, qint64)));
   fileWatcher->setFilePath(filePath);

   QVERIFY(outFile.open(QIODevice::Append | QIODevice::Text));

   stream << "This is the last line";
   stream.flush();
   outFile.close();

   spy.wait(5000);

   QVERIFY2(spy.count() == 1, "Signal for changed size wasn't emitted by timer event.");
   QVariantList parameters = spy.at(0);
   Q_ASSERT(parameters.count() == 2);

   qint64 oldSize = parameters.at(0).toInt();
   qint64 newSize = parameters.at(1).toInt();
   QVERIFY2(oldSize == offsetFileSize, "Offset size wasn't used as old size");
   QVERIFY2(newSize == outFile.size(), "New size isn't file's new size");
}

QTEST_MAIN(FileWatcherTest)

#include "tst_FileWatcherTest.moc"

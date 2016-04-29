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

#include <gui/file_views/FileListItemWidget.h>
#include <ui_FileListItemWidget.h>

class FileListItemWidgetTest : public QObject
{
   Q_OBJECT

public:
   FileListItemWidgetTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testSetFileName();
   void testSetLineCount();
   void testInitialFileState();
   void testCloseRequest();
};

FileListItemWidgetTest::FileListItemWidgetTest()
{
}

void FileListItemWidgetTest::initTestCase()
{
}

void FileListItemWidgetTest::cleanupTestCase()
{
}

void FileListItemWidgetTest::testSetFileName()
{
   QString testText("blabla.txt");
   FileListItemWidget listWidget;
   listWidget.setFileName(testText);

   QVERIFY2(listWidget.ui->fileNameLabel->text() == testText, "Filename wasn't set in gui");
   QVERIFY2(listWidget.fileName() == testText, "Filename wasn't returned.");
}

void FileListItemWidgetTest::testSetLineCount()
{
   quint64 lineCount = 45312;
   FileListItemWidget listWidget;
   listWidget.setLineCount(lineCount);

   QVERIFY2(listWidget.ui->lineCountLabel->text() == QString::number(lineCount),
            "Line count wasn't set in gui");
}

void FileListItemWidgetTest::testInitialFileState()
{
   FileListItemWidget listWidget;

   QVERIFY2(listWidget.fileState() == FileState::FileInSync, "Wrong default file state.");
}

void FileListItemWidgetTest::testCloseRequest()
{
   FileListItemWidget listWidget;
   QSignalSpy spy(&listWidget, SIGNAL(closeFileRequested()));

   QTest::mouseClick(listWidget.ui->closeButton, Qt::LeftButton);
   QVERIFY2(spy.count() == 1, "Close file request wasn't emitted");
}

QTEST_MAIN(FileListItemWidgetTest)

#include "tst_FileListItemWidgetTest.moc"
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

#include <gui/file_views/FileListItemView.h>
#include <gui/file_views/FileListItemWidget.h>

class FileListItemViewTest : public QObject
{
   Q_OBJECT

public:
   FileListItemViewTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testFeatures();
   void testCloseRequest();
   void testSetFileName();
};

FileListItemViewTest::FileListItemViewTest()
{
}

void FileListItemViewTest::initTestCase()
{
}

void FileListItemViewTest::cleanupTestCase()
{
}

void FileListItemViewTest::testFeatures()
{
   FileListItemView itemView;
   QVERIFY2(itemView.viewFeatures().testFlag(FileViewInterface::HasStateView),
            "List item view doesn't have state view enabled.");
   QVERIFY2(!itemView.viewFeatures().testFlag(FileViewInterface::HasTextView),
            "List item view has text view enabled.");
}

void FileListItemViewTest::testCloseRequest()
{
   FileListItemView itemView;
   QSignalSpy spy(&itemView, SIGNAL(requestCloseFile()));

   itemView.m_listWidget->closeFileRequested();

   QVERIFY2(spy.count() == 1, "Close request signal wasn't emitted once.");
}

void FileListItemViewTest::testSetFileName()
{
   QFileInfo fileInfo("testfile.log");
   FileListItemView itemView;
   itemView.setFileInfo(fileInfo);

   QVERIFY2(itemView.m_listWidget->fileName() == fileInfo.fileName(), "Filename wasn't set in list widget");
}

QTEST_MAIN(FileListItemViewTest)

#include "tst_FileListItemViewTest.moc"

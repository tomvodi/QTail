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
   void testSetFileActiveStateLineNumbers();
   void testSetFileStateWhenFileActive();
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

   // Text view flag is used for getting notified about new lines
   QVERIFY2(itemView.viewFeatures().testFlag(FileViewInterface::HasTextView),
            "List item view hasn't text view enabled.");
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
   QFileInfo fileInfo("testSetFileName.log");
   FileListItemView itemView;
   itemView.setFileInfo(fileInfo);

   QVERIFY2(itemView.m_listWidget->fileName() == fileInfo.fileName(), "Filename wasn't set in list widget");
}

/*!
 * \brief FileListItemViewTest::testSetFileActive
 * If the file view is set inactive, appending lines should result in increasing the line number
 * of the file list widget.
 * Setting the view active again, should clear the new lines number. In the active state,
 * appending lines shouldn't result in increasing the number.
 */
void FileListItemViewTest::testSetFileActiveStateLineNumbers()
{
   FileListItemView itemView;

   itemView.setFileActive(false);
   itemView.appendLine("line 1");
   itemView.appendLine("line 2");
   itemView.appendLine("line 3");

   QVERIFY2(itemView.m_listWidget->lineCount() == 3, "New lines count wasn't set with appendLine.");

   itemView.appendLines({ "line new", "line 41234"});

   QVERIFY2(itemView.m_listWidget->lineCount() == 5, "New lines count wasn't set with appendLines.");

   itemView.setFileActive(true);

   QVERIFY2(itemView.m_listWidget->lineCount() == 0, "New lines count wasn't set to 0");

   // Append lines in active state => no increasing of number
   itemView.appendLine("line 764568");
   itemView.appendLines({ "line new 2", "line 98576"});

   QVERIFY2(itemView.m_listWidget->lineCount() == 0, "Appending lines in active view increased lines number.");
}

void FileListItemViewTest::testSetFileStateWhenFileActive()
{
   FileListItemView itemView;

   itemView.setFileActive(true);
   itemView.setFileState(FileState::FileHasChanged);
   QVERIFY2(itemView.m_listWidget->fileState() == FileState::FileInSync, "File not in sync state when active");

   itemView.setFileActive(false);
   itemView.setFileState(FileState::FileHasChanged);
   QVERIFY2(itemView.m_listWidget->fileState() == FileState::FileHasChanged,
            "File not in sync state when inactive.");

   itemView.setFileActive(true);
   QVERIFY2(itemView.m_listWidget->fileState() == FileState::FileInSync,
            "File not in sync state when activated after changed state.");
}

QTEST_MAIN(FileListItemViewTest)

#include "tst_FileListItemViewTest.moc"

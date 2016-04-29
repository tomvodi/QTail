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

#include <TestCommon.h>
#include <gui/MainWindow.h>
#include <gui/file_views/PlainTextEdit.h>
#include <gui/file_views/FileListItemWidget.h>
#include <ui_MainWindow.h>

class MainWindowTest : public QObject
{
   Q_OBJECT

public:
   MainWindowTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testSetup();
   void testOpenFile_fileInList();
   void testOpenFile_noDuplicates();
   void testOpenFile_textEditVisible();
   void testIfHasFileListItemWidgetForOpenFile();
   void testClosingFileWithFileItemCloseButton();
};

MainWindowTest::MainWindowTest()
{
}

void MainWindowTest::initTestCase()
{
}

void MainWindowTest::cleanupTestCase()
{
}

void MainWindowTest::testSetup()
{
   MainWindow window;
   QVERIFY2(window.ui->fileListWidget->selectionMode() == QAbstractItemView::SingleSelection,
            "The file list widget is not in single select mode");
}

void MainWindowTest::testOpenFile_fileInList()
{
   QString filePath = TestCommon::generateExistingFilePath("testOpenFile_fileInList");
   MainWindow window;
   window.openFile(filePath);

   QListWidget *listWidget = window.ui->fileListWidget;

   QVERIFY2(listWidget->count() == 1, "File wasn't opened and added to list widget.");
   QVERIFY2(listWidget->selectedItems().count() == 1, "No item selected.");
   QListWidgetItem *firstItem = listWidget->item(0);
   QListWidgetItem *firstSelectedItem = listWidget->selectedItems().at(0);
   QVERIFY2(firstItem == firstSelectedItem, "The first row is not selected row.");
}

void MainWindowTest::testOpenFile_noDuplicates()
{
   QString filePath = TestCommon::generateExistingFilePath("testOpenFile_noDuplicates");
   MainWindow window;
   window.openFile(filePath);
   window.openFile(filePath);

   QListWidget *listWidget = window.ui->fileListWidget;

   QVERIFY2(listWidget->count() == 1, "File was opened a second time.");
}

void MainWindowTest::testOpenFile_textEditVisible()
{
   QString filePath = TestCommon::generateExistingFilePath("testOpenFile_textLoaded");

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);
   QString testText("This is a test text");
   stream << testText;
   outFile.close();

   QCoreApplication::processEvents();

   MainWindow window;
   window.openFile(filePath);

   // Check if opened file is current item
   QListWidgetItem *currentItem = window.ui->fileListWidget->currentItem();
   QString currentItemPath = currentItem->data(window.FilePathDataRole).toString();
   QVERIFY2(currentItemPath == filePath, "The recently opened file isn't the current item in the file list");

   // Check if correct text edit is visible
   MainWindow::FileViewItems viewItems = window.m_fileViewItems.value(filePath);
   QVERIFY2(viewItems.plainTextEdit() == window.ui->stackedWidget->currentWidget(),
            "The current visible text edit isn't the one of the most recent opened file.");
}

void MainWindowTest::testIfHasFileListItemWidgetForOpenFile()
{
   QString filePath = TestCommon::generateExistingFilePath("testOpenFile_textLoaded");

   MainWindow window;
   window.openFile(filePath);

   Q_ASSERT(window.ui->fileListWidget->count());
   auto item = window.ui->fileListWidget->item(0);
   QWidget *widget = window.ui->fileListWidget->itemWidget(item);
   FileListItemWidget *itemWidget = static_cast<FileListItemWidget*>(widget);
   QVERIFY2(itemWidget != 0, "File list widget doesn't use FileListItemWidgets");
   QVERIFY2(itemWidget->fileName() == "testOpenFile_textLoaded", "Filename wasn't set in list item widget.");
}

void MainWindowTest::testClosingFileWithFileItemCloseButton()
{
   QString filePath = TestCommon::generateExistingFilePath("testOpenFile_textLoaded");

   QFile outFile(filePath);
   outFile.open(QIODevice::WriteOnly);
   QTextStream stream(&outFile);
   QString testText("This is a test text");
   stream << testText;
   outFile.close();

   QCoreApplication::processEvents();

   MainWindow window;
   window.openFile(filePath);

   Q_ASSERT(window.ui->fileListWidget->count());
   auto item = window.ui->fileListWidget->item(0);
   QWidget *widget = window.ui->fileListWidget->itemWidget(item);
   FileListItemWidget *itemWidget = static_cast<FileListItemWidget*>(widget);
   Q_ASSERT(itemWidget);

   itemWidget->closeFileRequested();

   QVERIFY2(window.ui->fileListWidget->count() == 0, "File item wasn't removed from list for close request.");

   // Just because this was the last file closed, there shouldn't be any text edit in the stacked widget
   QVERIFY2(window.ui->stackedWidget->count() == 0, "At least one text edit is still in stacked widget after last file closed.");
}

QTEST_MAIN(MainWindowTest)

#include "tst_MainWindowTest.moc"

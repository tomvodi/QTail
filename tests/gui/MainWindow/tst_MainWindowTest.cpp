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
#include <gui/tools/Settings.h>
#include <ui_MainWindow.h>

class MainWindowTest : public QObject
{
   Q_OBJECT

public:
   MainWindowTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void init();
   void cleanup();
   void testSetup();
   void testOpenFile_fileInList();
   void testOpenFile_noDuplicates();
   void testOpenFile_textEditVisible();
   void testIfHasFileListItemWidgetForOpenFile();
   void testClosingFileWithFileItemCloseButton();
   void testOpenLastOpenedFiles();
   void testOpenRecentFilesMenu();

private:
   void clearLastOpenedFiles();
   void clearRecentlyOpenedFiles();
};

MainWindowTest::MainWindowTest()
{
   QCoreApplication::setOrganizationName("QTail");
   QCoreApplication::setApplicationName("MainWindowTest");
}

void MainWindowTest::initTestCase()
{
}

void MainWindowTest::cleanupTestCase()
{
}

void MainWindowTest::init()
{
   clearLastOpenedFiles();
   clearRecentlyOpenedFiles();
}

void MainWindowTest::cleanup()
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

void MainWindowTest::testOpenLastOpenedFiles()
{
   QString filePath1 = TestCommon::generateExistingFilePath("testOpenLastOpenedFiles1");
   QString filePath2 = TestCommon::generateExistingFilePath("testOpenLastOpenedFiles2");

   MainWindow *window = new MainWindow;
   window->openFile(filePath1);
   window->openFile(filePath2);
   Q_ASSERT(window->ui->fileListWidget->count() == 2);

   QListWidgetItem *firstItem = window->ui->fileListWidget->item(0);
   QString firstItemPath = firstItem->data(window->FilePathDataRole).toString();
   Q_ASSERT(firstItemPath == filePath1);

   // If file is closed, it shouldn't be opened on next startup
   window->closeFileItem(window->ui->fileListWidget->item(1));

   window->close();
   delete window;

   window = new MainWindow;
   QVERIFY2(window->ui->fileListWidget->count() < 2, "Closed file wasn't removed from last opened files list.");
   QVERIFY2(window->ui->fileListWidget->count() == 1, "Last opened files weren't opened again.");

   firstItem = window->ui->fileListWidget->item(0);
   firstItemPath = firstItem->data(window->FilePathDataRole).toString();
   QVERIFY2(firstItemPath == filePath1, "Last opened files were opened in wrong order.");
}

void MainWindowTest::testOpenRecentFilesMenu()
{
   QFileInfo file1(TestCommon::generateExistingFilePath("testOpenRecentFilesFile1"));
   QFileInfo file2(TestCommon::generateExistingFilePath("testOpenRecentFilesFile2"));

   MainWindow *window = new MainWindow;
   window->openFile(file1.absoluteFilePath());
   window->openFile(file2.absoluteFilePath());

   // Test if all actions are present and in the correct order
   auto actions = window->ui->menuRecentFiles->actions();
   QVERIFY2(actions.count() == 2, "No actions were added to recent files menu");
   QVERIFY2(actions.first()->text().contains(file2.fileName()), "Second opened file isn't at first position in recent file menu");

   // Now, if both files are closed, and the first file is opened again,
   // the first file should be at the first position and
   // the list should only contain two items because the first file is already in the list.
   window->closeFileItem(window->ui->fileListWidget->item(0));
   window->closeFileItem(window->ui->fileListWidget->item(0));

   window->openFile(file1.absoluteFilePath());
   actions = window->ui->menuRecentFiles->actions();
   QVERIFY2(actions.count() == 2, "An action was added to action list, despite the file is already in list.");
   QVERIFY2(actions.first()->text().contains(file1.fileName()), "Reopened first files isn't at first position in recent file menu");

   window->closeFileItem(window->ui->fileListWidget->item(0));
   window->close();
   delete window;

   // Check if recently opened files list is loaded on startup.
   window = new MainWindow;

   actions = window->ui->menuRecentFiles->actions();
   QVERIFY2(actions.count() == 2, "Recently opened files weren't stored into settings and loaded on startup.");
   QVERIFY2(actions.first()->text().contains(file2.fileName()), "Recently opened files were stored in the wrong order.");

   // Test if triggering an recent file action results in opening this file.
   Q_ASSERT(window->ui->fileListWidget->count() == 0);
   actions = window->ui->menuRecentFiles->actions();
   Q_ASSERT(actions.count() == 2);
   QAction *action = actions.at(1);
   action->trigger();
   QVERIFY2(window->ui->fileListWidget->count() == 1, "File wasn't opened after triggering a recently opened files action");
   QListWidgetItem *item = window->ui->fileListWidget->item(0);
   QString filePathInItem = item->data(window->FilePathDataRole).toString();
   QString actionFilePath = action->data().toString();
   QVERIFY2(filePathInItem == actionFilePath, "Wrong file was opened by triggering a recently opened files action.");
}

void MainWindowTest::clearLastOpenedFiles()
{
   Settings settings;
   settings.setLastOpenedFiles(QStringList());
}

void MainWindowTest::clearRecentlyOpenedFiles()
{
   Settings settings;
   settings.setRecentlyOpenedFiles(QStringList());
}

QTEST_MAIN(MainWindowTest)

#include "tst_MainWindowTest.moc"

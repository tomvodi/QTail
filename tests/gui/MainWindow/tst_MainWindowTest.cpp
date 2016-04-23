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
#include <gui/PlainTextEdit.h>
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
    void testOpenFile_textLoaded();
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
    QVERIFY2(window.m_textEdit->isReadOnly(), "Text edit isn't read only");
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

void MainWindowTest::testOpenFile_textLoaded()
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

    QString textEditText = window.m_textEdit->toPlainText();
    QVERIFY2(textEditText == testText, "Text wasn't loaded into text edit");
}

QTEST_MAIN(MainWindowTest)

#include "tst_MainWindowTest.moc"

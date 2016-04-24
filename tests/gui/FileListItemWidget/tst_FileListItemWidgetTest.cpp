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

#include <gui/FileListItemWidget.h>
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
    void testFileState();
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

void FileListItemWidgetTest::testFileState()
{
    FileListItemWidget listWidget;

    QVERIFY2(listWidget.fileState() == FileListItemWidget::FileState::FileError, "Wrong default file state.");
}

QTEST_MAIN(FileListItemWidgetTest)

#include "tst_FileListItemWidgetTest.moc"

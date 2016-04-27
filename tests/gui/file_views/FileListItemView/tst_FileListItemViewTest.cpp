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

class FileListItemViewTest : public QObject
{
   Q_OBJECT

public:
   FileListItemViewTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testFeatures();
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

QTEST_MAIN(FileListItemViewTest)

#include "tst_FileListItemViewTest.moc"

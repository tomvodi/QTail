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
#include <FileReadLogic.h>

class FileReadLogicTest : public QObject
{
   Q_OBJECT

public:
   FileReadLogicTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testDefault();
};

FileReadLogicTest::FileReadLogicTest()
{
}

void FileReadLogicTest::initTestCase()
{
}

void FileReadLogicTest::cleanupTestCase()
{
}

void FileReadLogicTest::testDefault()
{
   QVERIFY2(true, "Failure");
}

QTEST_MAIN(FileReadLogicTest)

#include "tst_FileReadLogicTest.moc"

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
#include <ReloadAppendLogic.h>

class ReloadAppendLogicTest : public QObject
{
   Q_OBJECT

public:
   ReloadAppendLogicTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
//   void testDefault();
//   void testSetNewSize();
//   void testNewFile();
};

ReloadAppendLogicTest::ReloadAppendLogicTest()
{
}

void ReloadAppendLogicTest::initTestCase()
{
}

void ReloadAppendLogicTest::cleanupTestCase()
{
}

//void ReloadAppendLogicTest::testDefault()
//{
//   ReloadAppendLogic logic;
//   QVERIFY2(logic.shouldReload() == true, "Wrong default value");
//   QVERIFY2(logic.oldSize() == 0, "Wrong old size");
//}

//void ReloadAppendLogicTest::testSetNewSize()
//{
//   ReloadAppendLogic logic;
//   logic.setNewSize(123);

//   QVERIFY2(logic.oldSize() == 123, "Wrong old size");
//}

//void ReloadAppendLogicTest::testNewFile()
//{
//   QFileInfo fileInfo(TestCommon::generateExistingFilePath("testNewFile.log"));
//   ReloadAppendLogic logic;
//   logic.setFile(fileInfo);

//   QFile outFile(fileInfo.absoluteFilePath());
//   outFile.open(QIODevice::WriteOnly);
//   QTextStream stream(&outFile);
//   stream << "Test text";
//   stream.flush();

//   TestCommon::waitMsecs(100);

//}

QTEST_MAIN(ReloadAppendLogicTest)

#include "tst_ReloadAppendLogicTest.moc"

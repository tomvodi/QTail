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

class TailEngineTest : public QObject
{
    Q_OBJECT

public:
    TailEngineTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

TailEngineTest::TailEngineTest()
{
}

void TailEngineTest::initTestCase()
{
}

void TailEngineTest::cleanupTestCase()
{
}

void TailEngineTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(TailEngineTest)

#include "tst_TailEngineTest.moc"

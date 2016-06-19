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

class FilterRuleTest : public QObject
{
   Q_OBJECT

public:
   FilterRuleTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testCase1();
};

FilterRuleTest::FilterRuleTest()
{
}

void FilterRuleTest::initTestCase()
{
}

void FilterRuleTest::cleanupTestCase()
{
}

void FilterRuleTest::testCase1()
{
   QVERIFY2(true, "Failure");
}

QTEST_MAIN(FilterRuleTest)

#include "tst_FilterRuleTest.moc"

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

class FilterDialogTest : public QObject
{
   Q_OBJECT

public:
   FilterDialogTest();

private Q_SLOTS:
   void initTestCase();
   void cleanupTestCase();
   void testCase1();
};

FilterDialogTest::FilterDialogTest()
{
}

void FilterDialogTest::initTestCase()
{
}

void FilterDialogTest::cleanupTestCase()
{
}

void FilterDialogTest::testCase1()
{
   QVERIFY2(true, "Failure");
}

QTEST_MAIN(FilterDialogTest)

#include "tst_FilterDialogTest.moc"
